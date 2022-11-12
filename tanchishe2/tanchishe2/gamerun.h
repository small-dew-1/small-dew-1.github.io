void initial(); //初始化游戏（生成游戏地图，蛇头，食物及其位置)

void printmap(); //生成游戏地图

void printsnake(); //打印出初始蛇的位置（后续只需要修改头尾即可）

void printfood(); //随机生成食物

void addhead(int x, int y); //添加蛇头，把旧蛇头变成蛇身

void deletetail(); //删除蛇尾

bool eatfood(); //判断是否吃掉食物

void move(); //重点函数，用于蛇的移动相关操作（更改方向，更新蛇位置，判断是否吃掉食物

bool hitwall(); //判断是否撞墙和蛇身，游戏结束标志

void freelist(); //游戏结束时要清除所有开辟空间，防止内存泄漏

void gameover(); //进行游戏结束操作结算
