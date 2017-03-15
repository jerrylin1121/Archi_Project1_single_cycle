#include <set>
#define HI 32
#define LO 33
#define PC 34

extern int reg_value[35];
extern std::set<int> changing_set;

void show_all_reg(void);
void show_change_reg(void);
