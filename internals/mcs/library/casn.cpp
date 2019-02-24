// Copyright (C) by Vesa Karvonen

#include "mcs/casn.hpp"
#include "mcs/config.hpp"

#include "dumpster_v1/insertion_sort.hpp"

bool mcs::CASN::casn(op_mono_t *mono_ops) {
  if (!mono_ops->op)
    return true;

  dumpster::insertion_sort(
      mono_ops,
      [](auto lhs, auto rhs) {
        return reinterpret_cast<size_t>(&lhs.op->atom) <
               reinterpret_cast<size_t>(&rhs.op->atom);
      },
      [](auto mono_op) { return !mono_op.op; });

  return mono_ops->op->step(mono_ops->op, mono_ops + 1);
}
