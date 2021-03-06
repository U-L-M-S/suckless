/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */

static const unsigned int snap      = 8;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;     /* 0 means no bar */
static const int topbar             = 1;     /* 0 means bottom bar */

static const char *fonts[]          = { "monospace:size=8", "Hack Nerd Font:size=8" };
static const char dmenufont[]       = "Hack Nerd Font:size=8";

static const unsigned int gappx     = 6;
//
// static const char col_gray1[]       = "#282a36"; // Numbers Background
// static const char col_gray2[]       = "#282a36"; // DK (it doesn't show up)
// static const char col_gray3[]       = "#96b5b4"; // Letter
// static const char col_gray4[]       = "#d7d7d7"; // Title Color
// static const char col_cyan[]        = "#4d4d4d"; // Title Background
//


static const char col_gray1[]       = "#282a36"; // Numbers Background
static const char col_gray2[]       = "#644475"; // DK (it doesn't show up)
static const char col_gray3[]       = "#f8f8f2"; // Letter
static const char col_gray4[]       = "#282a36"; // Title Color
static const char col_gray5[]       = "#a272a4"; 
static const char col_cyan[]        = "#bf93f9"; // Title Background
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_gray5 },
};

/* tagging */
static const char *tags[] = { "???", "???", "???", "???", "???", "???"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "st-256color",       NULL,           NULL,      0,          0,           1,          0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[???]",      tile },    /* first entry is default */
	{ "[???]",      NULL },    /* no layout function means floating behavior */
	{ "[???]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }


/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *web[] = { "brave-browser", NULL };
// static const char *pic[] = { "zsh", "~/.local/bin/screenshot", NULL };


#include <X11/XF86keysym.h>

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key             function        argument */
	{ MODKEY,                       XK_space,       spawn,          {.v = dmenucmd } },
	{ MODKEY,	                      XK_Return,      spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_p,           spawn,          SHCMD("~/.local/bin/screenshot") },
	{ MODKEY,                       XK_7,           spawn,          SHCMD("keepassxc") },
	{ MODKEY,                       XK_8,           spawn,          SHCMD("discord") },
	{ MODKEY,                       XK_u,           spawn,          SHCMD("signal-desktop") },
	{ MODKEY,                       XK_9,           spawn,          SHCMD("WhatsApp ") },
	{ MODKEY,                       XK_z,           spawn,          SHCMD("telegram") },
	{ MODKEY,			                  XK_b,	          spawn,      	  {.v = web } },
	{ MODKEY,                       XK_n,           togglebar,      {0} },
	{ MODKEY,                       XK_j,           focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,           focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
  { MODKEY,                       XK_i,           incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,           incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,           setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,           setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,         view,           {0} },
	{ MODKEY,	                      XK_c,           killclient,     {0} },
	{ MODKEY,                       XK_w,           setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_e,           setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_r,           setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_t,           setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,       togglefloating, {0} },
	{ MODKEY,                       XK_v,           view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_v,           tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,       focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,      focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,       tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,      tagmon,         {.i = +1 } },
  // Keypad
 //  TAGKEYS(                        XK_KP_1,                           0)
	// TAGKEYS(                        XK_KP_2,                           1)
	// TAGKEYS(                        XK_KP_3,                           2)
	// TAGKEYS(                        XK_KP_4,                           3)
	// TAGKEYS(                        XK_KP_5,                           4)
	// TAGKEYS(                        XK_KP_6,                           5)
  //
  TAGKEYS(                        XK_1,                              0)
	TAGKEYS(                        XK_2,                              1)
	TAGKEYS(                        XK_3,                              2)
	TAGKEYS(                        XK_4,                              3)
	TAGKEYS(                        XK_5,                              4)
	TAGKEYS(                        XK_6,                              5)
	// TAGKEYS(                        XK_7,                      6)
	// TAGKEYS(                        XK_8,                      7)
	// TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,            quit,          {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

