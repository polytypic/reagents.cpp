// Copyright (C) by Vesa Karvonen
#pragma once

#include "mcs/casn_synopsis.hpp"
#include "mcs/config.hpp"

#include "mcs_v1/lock.hpp"

#include <atomic>
#include <utility>

namespace mcs {

class CASN_detail : CASN {
  friend CASN;

  class atom_base_t;

  struct op_base_t;

  template <class Value> static bool step(op_base_t *op_base, op_mono_t *next);
};

} // namespace mcs

class mcs::CASN_detail::atom_base_t {
  friend struct CASN;
  friend class CASN_detail;

  Lock::lock_t lock;
};

template <class Value> struct mcs::CASN::atom_t : CASN_detail::atom_base_t {
  atom_t(Value &&value) : value(std::move(value)) {}
  atom_t(const Value &value) : value(value) {}

private:
  friend struct CASN;
  friend class CASN_detail;

  std::atomic<Value> value;
};

template <class Value>
mcs::CASN::atom_t<std::remove_cvref_t<Value>> mcs::CASN::atom(Value &&value) {
  return atom_t<Value>(std::forward<Value>(value));
}

template <class Value> Value mcs::CASN::load(const CASN::atom_t<Value> &atom) {
  return atom.value;
}

template <class Value, class Forwardable_Value>
void mcs::CASN::store(atom_t<Value> &atom, Forwardable_Value &&desired) {
  Lock::holding(atom.lock, [&]() {
    atom.value = std::forward<Forwardable_Value>(desired);
  });
}

struct mcs::CASN_detail::op_base_t {
  atom_base_t &atom;
  bool (&step)(op_base_t *op_base, op_mono_t *next);
};

template <class Value> struct mcs::CASN::op_t : CASN_detail::op_base_t {
  Value expected;
  Value desired;
};

struct mcs::CASN::op_mono_t {
  CASN_detail::op_base_t *op;
};

template <class Value>
bool mcs::CASN_detail::step(op_base_t *op_base, CASN::op_mono_t *next) {
  op_t<Value> &op = static_cast<op_t<Value> &>(*op_base);
  atom_t<Value> &atom = static_cast<atom_t<Value> &>(op.atom);

  return Lock::holding(atom.lock, [&]() {
    if (atom.value != op.expected)
      return false;
    if (next->op && !next->op->step(next->op, next + 1))
      return false;
    atom.value = op.desired;
    return true;
  });
}

template <class Value, class Forwardable_Expected, class Forwardable_Desired>
mcs::CASN::op_t<Value> mcs::CASN::op(atom_t<Value> &atom,
                                     Forwardable_Expected &&expected,
                                     Forwardable_Desired &&desired) {
  return {{atom, CASN_detail::step<Value>},
          std::forward<Forwardable_Expected>(expected),
          std::forward<Forwardable_Desired>(desired)};
}

template <class Value>
mcs::CASN::op_mono_t mcs::CASN::as_mono(op_t<Value> &op) {
  return {&op};
}

template <class... Compare_Exchanges>
bool mcs::CASN::casn(Compare_Exchanges &&... ops) {
  op_mono_t op_bases[] = {as_mono(ops)..., {nullptr}};
  return casn(op_bases);
}
