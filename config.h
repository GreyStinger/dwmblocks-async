#ifndef CONFIG_H
#define CONFIG_H

// #define CPU_COMMAND "top -bn1 | grep \"Cpu(s)\" | sed \"s/.*, *\([0-9.]*\)%* id.*/\1/\" | awk '{print 100 - $1\"%\"}'"
#define CPU_COMMAND "top -bn2 | grep \"Cpu(s)\" | tail -n 1 " \
    "| awk '{usage=100-$8} END {printf(\"%.2f%%\", usage)}'"

#define MEM_COMMAND "free -h | awk '"   \
    "/^Mem/ {"                          \
        "used = $3;"                    \
        "total = $2;"                   \
        "gsub(/|i/, \"\", used);"       \
        "gsub(/|i/, \"\", total);"      \
    "print used \"/\" total"            \
"}'"

#define POWER_COMMAND "echo $(cat /sys/class/power_supply/BAT0/capacity)%"

// This one will not but I need a bigger screen than I currently have to be
// happy with it
#define STORAGE_COMMAND "btrfs filesystem usage / 2>/dev/null | awk '"      \
    "/Overall/ {overall=1}"                                                 \
    "/Device size:/ && overall {total=$3}"                                  \
    "/Used:/ && overall {used=$2}"                                          \
    "/Free \\(estimated\\):/ && overall {free=$3; overall=0}"               \
    "END {"                                                                 \
    "printf \"%s/%s\", used, total;"                                        \
"}'"
//     "printf \"%s/%s (%s)\", used, total, free;"                             \
// "}'"

// String used to delimit block outputs in the status.
#define DELIMITER "  "

// Maximum number of Unicode characters that a block can output.
#define MAX_BLOCK_OUTPUT_LENGTH 45

// Control whether blocks are clickable.
#define CLICKABLE_BLOCKS 0

// Control whether a leading delimiter should be prepended to the status.
#define LEADING_DELIMITER 1

// Control whether a trailing delimiter should be appended to the status.
#define TRAILING_DELIMITER 1

// Define blocks for the status feed as X(icon, cmd, interval, signal).
#define BLOCKS(X)                               \
     X(" ", CPU_COMMAND, 2, 6)                 \
     X("  ", MEM_COMMAND, 30, 7)               \
     X("󱈏  ", POWER_COMMAND, 30, 7)               \
     X("󰋊 ", STORAGE_COMMAND, 60, 8)            \
     X(" ", "date '+%H:%M %a %d %h'", 1, 10)
//     X("󱑁 ", "date '+%H:%M %a %d %h'", 1, 10)
//     X(" ", "date '+%Y-%m-%d'", 60, 9)                                     \
//     X("", "sb-music", 0, 2)   \
//     X("", "sb-disk", 1800, 3) \
//     X("", "sb-memory", 10, 4) \
//     X("", "sb-loadavg", 5, 5) \
//     X("", "sb-mic", 0, 6)     \
//     X("", "sb-record", 0, 7)  \
//     X("", "sb-volume", 0, 8)  \
//     X("", "sb-battery", 5, 9) \

#endif  // CONFIG_H
