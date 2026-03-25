#include "../headers/utility.h"

Color Ccol = {
    132, 177, 121, 255};

Color Bocol = {
    174, 183, 132, 255};

Color Mencol = {
    232, 245, 189, 255};

Color Tcol = {
    162, 203, 139, 255};

Color Butcol1 = {
    165, 200, 158, 255};

Color Butcol2 = {
    165, 200, 158, 255};

Color Butcol3 = {
    165, 200, 158, 255};

Color Textcol = {
    98, 148, 89, 255};

bool hoverButton(Rectangle rec)
{
    return CheckCollisionPointRec(GetMousePosition(), rec);
}