#include <X11/XF86keysym.h>

/* alt-tab configuration */
static const unsigned int tabModKey 		= 0x40;	/* if this key is hold the alt-tab functionality stays acitve. This key must be the same as key that is used to active functin altTabStart `*/
static const unsigned int tabCycleKey 		= 0x17;	/* if this key is hit the alt-tab program moves one position forward in clients stack. This key must be the same as key that is used to active functin altTabStart */
static const unsigned int tabPosY 			= 1;	/* tab position on Y axis, 0 = bottom, 1 = center, 2 = top */
static const unsigned int tabPosX 			= 1;	/* tab position on X axis, 0 = left, 1 = center, 2 = right */
static const unsigned int maxWTab 			= 600;	/* tab menu width */
static const unsigned int maxHTab 			= 50;	/* tab menu height */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 0;        /* horizontal padding for statusbar */
static const int vertpadbar         = 3;        /* vertical padding for statusbar */
static const char *fonts[]          = { "Tamzen:pixelsize=16" };
static const char dmenufont[]       = "Tamzen:pixelsize=16";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#fffefe";
static const char col_gray3[]       = "#fffefe";
static const char col_gray4[]       = "#fffefe";
static const char col_cyan[]        = "#800000";
static const char col_unfocus[]     = "#3d3d3d";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray4, col_gray1, col_unfocus },
	[SchemeSel]  = { col_gray2, col_cyan,  col_gray1 },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask,              KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

#include "patch/shift-tools.c"
static const Key keys[] = {
	/* modifier                     key                           function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_q,	   view,           {0} },
	{ MODKEY|Mod1Mask,              XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|Mod1Mask,              XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|Mod1Mask,              XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_equal,  setgaps,        {.i = 0 } },
	{ MODKEY,                       XK_Left,   shiftview,      {.i = -1} },
	{ MODKEY,                       XK_Right,  shiftview,      {.i = +1} },
	{ MODKEY|Mod1Mask,              XK_Left,   shifttag,       {.i = -1} },
	{ MODKEY|Mod1Mask,              XK_Right,  shifttag,       {.i = +1} },
	{ Mod1Mask,                     XK_Tab,    altTabStart,    {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|Mod1Mask,              XK_q,      quit,           {0} },
	{ MODKEY|Mod1Mask,              XK_Return,                spawn, SHCMD("runterminal.sh") },
	{ MODKEY|Mod1Mask,              XK_s,                     spawn, SHCMD("screenshotssh.sh box") },
	{ MODKEY,                       XK_e,                     spawn, SHCMD("runemacs.sh") },
	{ MODKEY,                       XK_c,                     spawn, SHCMD("xcolor.sh") },
	{ 0,                            XF86XK_MonBrightnessUp,   spawn, SHCMD("xbacklight -inc 5") },
	{ 0,                            XF86XK_MonBrightnessDown, spawn, SHCMD("xbacklight -dec 5") },
	{ 0,                            XF86XK_AudioMute,         spawn, SHCMD("amixer -D pulse set Master toggle && kill -44 $(pidof dwmblocks)") },
	{ 0,                            XF86XK_AudioRaiseVolume,  spawn, SHCMD("amixer -D pulse set Master 5%+ && kill -44 $(pidof dwmblocks)") },
	{ 0,                            XF86XK_AudioLowerVolume,  spawn, SHCMD("amixer -D pulse set Master 5%- && kill -44 $(pidof dwmblocks)") }
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

