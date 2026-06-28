#include "../headers/utility.h"

Color Ccol = {
    132, 177, 121, 255};

Color Bocol = {
    174, 183, 132, 255};

Color Mencol = {
    232, 245, 189, 255};

Color Tcol = {
    162, 203, 139, 255};

Color Pcol = {
    29, 84, 109, 255};

Color Butcol1 = {
    165, 200, 158, 255};

Color Butcol2 = {
    165, 200, 158, 255};

Color Butcol3 = {
    165, 200, 158, 255};

Color Butcol4 = {
    165, 200, 158, 255};

Color Textcol = {
    98, 148, 89, 255};

bool hoverButton(Rectangle rec)
{
    return CheckCollisionPointRec(GetMousePosition(), rec);
}

void ShowMessage(const char *msg, int padding, Postions pos, Color col, int fontSize)
{
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();
    int textWidth = MeasureText(msg, fontSize);
    int boxW = textWidth + (padding * 2);
    int boxH = fontSize + (padding * 2);
    Vector2 boxPos = {0};

    switch (pos)
    {
    case TOP_LEFT:
        boxPos = (Vector2){20, 20};
        break;
    case TOP_MIDDLE:
        boxPos = (Vector2){(screenW - boxW) / 2.0f, 20};
        break;
    case TOP_RIGHT:
        boxPos = (Vector2){screenW - boxW - 20.0f, 20};
        break;
    case CENTER:
        boxPos = (Vector2){(screenW - boxW) / 2.0f, (screenH - boxH) / 2.0f};
        break;
    case BOTTOM_MIDDLE:
        boxPos = (Vector2){(screenW - boxW) / 2.0f, screenH - boxH - 20.0f};
        break;
    case BOTTOM_LEFT:
        boxPos = (Vector2){20, screenH - boxH - 20.0f};
        break;
    case BOTTOM_RIGHT:
        boxPos = (Vector2){screenW - boxW - 20.0f, screenH - boxH - 20.0f};
        break;
    }

    DrawRectangleRec(
        (Rectangle){
            boxPos.x,
            boxPos.y,
            (float)boxW,
            (float)boxH},
        Fade(col, 0.8f));
    DrawRectangleLinesEx(
        (Rectangle){
            boxPos.x,
            boxPos.y,
            (float)boxW,
            (float)boxH},
        2, WHITE);
    DrawText(
        msg,
        (int)(boxPos.x + padding),
        (int)(boxPos.y + padding),
        fontSize, WHITE);
}

float MeasureTextHeight(char *text, int fontSize)
{
    return MeasureTextEx(GetFontDefault(), text, fontSize, 2.0).y;
}

bool DrawCard(Card card)
{
    DrawRectangleRec(
        card.rec,
        card.CardColor);

    // Image place holder
    // DrawRectangle(
    //     card.rec.x + 15,
    //     card.rec.y + 15,
    //     30,
    //     MeasureTextHeight(card.Head, 30),
    //     BLACK);
    DrawTexture(
        card.img,
        card.rec.x + 15,
        card.rec.y + 15,
        WHITE);

    DrawText(
        card.Head,
        card.rec.x + 15 + 30 + 10, // rec.x + padding1 + font size (which also the width of rec box holder) + padding2
        card.rec.y + 15,           // rec.x + padding1
        30,
        card.TextColor);
    DrawText(
        card.body,
        card.rec.x + 15,                                         // rec.x + padding1
        card.rec.y + MeasureTextHeight(card.Head, 30) + 15 + 10, // rec.x + height of the head text +  padding1 + padding2
        15,
        card.TextColor);

    return hoverButton(card.rec);
}