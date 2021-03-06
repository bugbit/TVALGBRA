/*---------------------------------------------------------*/
/*                                                         */
/*   Turbo Vision Hello World Demo Source File             */
/*                                                         */
/*---------------------------------------------------------*/
/*
 *      Turbo Vision - Version 2.0
 *
 *      Copyright (c) 1994 by Borland International
 *      All Rights Reserved.
 *
 */

#define Uses_TKeys
#define Uses_TApplication
#define Uses_TEvent
#define Uses_TRect
#define Uses_TDialog
#define Uses_TStaticText
#define Uses_TButton
#define Uses_TMenuBar
#define Uses_TSubMenu
#define Uses_TMenuItem
#define Uses_TStatusLine
#define Uses_TStatusItem
#define Uses_TStatusDef
#define Uses_TDeskTop
#include <tvision/tv.h>
#include "tvalgbra.h"
#include "gadgets.h"

TTVAlgebraApp::TTVAlgebraApp() :
    TProgInit(&TTVAlgebraApp::initStatusLine,
        &TTVAlgebraApp::initMenuBar,
        &TTVAlgebraApp::initDeskTop
    )
{
    TRect r = getExtent();                      // Create the clock view.
    r.a.x = r.b.x - 9;      r.b.y = r.a.y + 1;
    clock = new TClockView(r);
    insert(clock);

    r = getExtent();                            // Create the heap view.
    r.a.x = r.b.x - 13;     r.a.y = r.b.y - 1;
    heap = new THeapView(r);
    insert(heap);
}

void TTVAlgebraApp::greetingBox()
{
    TDialog* d = new TDialog(TRect(25, 5, 55, 16), "Hello, World!");

    d->insert(new TStaticText(TRect(3, 5, 15, 6), "How are you?"));
    d->insert(new TButton(TRect(16, 2, 28, 4), "Terrific", cmCancel, bfNormal));
    d->insert(new TButton(TRect(16, 4, 28, 6), "Ok", cmCancel, bfNormal));
    d->insert(new TButton(TRect(16, 6, 28, 8), "Lousy", cmCancel, bfNormal));
    d->insert(new TButton(TRect(16, 8, 28, 10), "Cancel", cmCancel, bfNormal));

    deskTop->execView(d);
    destroy(d);
}

void TTVAlgebraApp::handleEvent(TEvent& event)
{
    TApplication::handleEvent(event);
    if (event.what == evCommand)
    {
        switch (event.message.command)
        {
        case GreetThemCmd:
            greetingBox();
            clearEvent(event);
            break;
        default:
            break;
        }
    }
}

TMenuBar* TTVAlgebraApp::initMenuBar(TRect r)
{

    r.b.y = r.a.y + 1;

    return new TMenuBar(r,
        *new TSubMenu("TV~A~lgebra", kbAltH) +
        *new TMenuItem("~G~reeting...", GreetThemCmd, kbAltG) +
        newLine() +
        *new TMenuItem("E~x~it", cmQuit, cmQuit, hcNoContext, "Alt-X")
    );

}

TStatusLine* TTVAlgebraApp::initStatusLine(TRect r)
{
    r.a.y = r.b.y - 1;
    return new TStatusLine(r,
        *new TStatusDef(0, 0xFFFF) +
        *new TStatusItem("~Alt-X~ Exit", kbAltX, cmQuit) +
        *new TStatusItem(0, kbF10, cmMenu)
    );
}

void TTVAlgebraApp::idle()
{
    TProgram::idle();
    clock->update();
    heap->update();
}

int main()
{
    TTVAlgebraApp helloWorld;
    helloWorld.run();
    return 0;
}
