#ifndef AOC_DAYS_H
#define AOC_DAYS_H

#define STUB  { using Day = aoc::DayAPI;}

#ifdef DAY00
#include "00/day.hpp"
#else 
namespace day00 STUB
#endif
#ifdef DAY01
#include "01/day.hpp"
#else
namespace day01 STUB
#endif
#ifdef DAY02
#include "02/day.hpp"
#else
namespace day02 STUB
#endif
#ifdef DAY03
#include "03/day.hpp"
#else
namespace day03 STUB
#endif
#ifdef DAY04
#include "04/day.hpp"
#else
namespace day04 STUB
#endif
#ifdef DAY05
#include "05/day.hpp"
#else
namespace day05 STUB
#endif
#ifdef DAY06
#include "06/day.hpp"
#else
namespace day06 STUB
#endif
#ifdef DAY07
#include "07/day.hpp"
#else
namespace day07 STUB
#endif
#ifdef DAY08
#include "08/day.hpp"
#else
namespace day08 STUB
#endif
#ifdef DAY09
#include "09/day.hpp"
#else
namespace day09 STUB
#endif
#ifdef DAY10
#include "10/day.hpp"
#else
namespace day10 STUB
#endif
#ifdef DAY11 
#include "11/day.hpp" 
#else
namespace day11 STUB
#endif
#ifdef DAY12
#include "12/day.hpp"
#else
namespace day12 STUB
#endif
#ifdef DAY13
#include "13/day.hpp"
#else
namespace day13 STUB
#endif
#ifdef DAY14
#include "14/day.hpp"
#else
namespace day14 STUB
#endif
#ifdef DAY15
#include "15/day.hpp"
#else
namespace day15 STUB
#endif
#ifdef DAY16
#include "16/day.hpp"
#else
namespace day16 STUB
#endif
#ifdef DAY17
#include "17/day.hpp"
#else
namespace day17 STUB
#endif
#ifdef DAY18
#include "18/day.hpp"
#else
namespace day18 STUB
#endif
#ifdef DAY19
#include "19/day.hpp"
#else
namespace day19 STUB
#endif
#ifdef DAY20
#include "20/day.hpp"
#else
namespace day20 STUB
#endif
#ifdef DAY21
#include "21/day.hpp"
#else
namespace day21 STUB
#endif
#ifdef DAY22
#include "22/day.hpp"
#else
namespace day22 STUB
#endif
#ifdef DAY23
#include "23/day.hpp"
#else
namespace day23 STUB
#endif
#ifdef DAY24
#include "24/day.hpp"
#else
namespace day24 STUB
#endif
#ifdef DAY25
#include "25/day.hpp"
#else
namespace day25 STUB
#endif

#endif
