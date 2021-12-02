/* 来源于 RainbowRoad1 的 14 行贪吃蛇 */
/* https://github.com/RainbowRoad1/Cgame */

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/* 消除光标 */
void Hidecursor();

int main()
{
    Hidecursor();

    /* 地图大小 */
    int Width = 20, Size = Width * Width;

    /* 数组map存储整个地图的信息 */
    /* >0:蛇身  =0:空地  -1:食物 */
    int *map = (int *)calloc(Size, 4);

    /* 初始化食物位置 */
    srand((unsigned int)map);

    /* 蛇头坐标 */
    /* snakehead[0]:X轴 snakehead[1]:Y轴 */
    /* food = 0 时吃到了食物 ; food = 1 时正常 */
    int snakehead[2] = {0};
    int snakelength = 3, action_now = 'D', action_hit, food;

    int i, *p;

    /* 键入ESC退出循环 */
    for (action_hit = map[1] = -1; action_hit - 27; Sleep(1000))
    {
        //输入检测
        if (kbhit())
        {
            //获取输入，大小转化 ('awsd'会转为'AWSD')
            action_hit = getch() & 95;
            //冲突检测 , 更新动作
            //键入不是"AWSD"中的一个 , 那么 || 前面为 1 ,  即不会执行 || 后面语句
            //" (action_hit ^ action_now) & 20 ^ 4 " 判断不能反着走
            (action_hit - 65 && action_hit - 68 && action_hit - 83 && action_hit - 87) || ((((action_hit ^ action_now) & 20) ^ 4) && (action_now = action_hit));
        }

        /* p指向 X 或 Y , 在于 action_now 的值 */
        p = snakehead + !!(action_now & 2);

        /* 对其头进行合理的移动 */
        *p += (action_now / 3) & 2;
        --*p;

        /* 越界的处理 , (--*p + Width)中 Width 的引入在于 --*p 可能为负 */
        *p = (*p + Width) % Width;

        /* food = 1 */
        food = !system("cls");

        /* p 指向蛇头对应的地图值 */
        *(p = map + snakehead[0] + snakehead[1] * Width) > 0 && (action_hit = 27);

        // *p != 0 时执行 && 后面
        for (; *p && (map[i = rand() % Size] || (--map[i], ++snakelength, --food));)
        {
            ;
        }

        for (i = 0, *p = snakelength; i < Size; (++i % Width) || printf("|\n"))
        {
            printf(map[i] > 0 ? (map[i] -= food, "()") : (map[i] ? "00" : "  "));
        }
    }
}

void Hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}
