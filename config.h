/* See LICENSE file for copyright and license details. */

#define STATUSPAD	-2
#define MFACTOR 	0.50
#define NUMCOLORS	7


static const char *fonts[] = {
    "ohsnap:size=10",
    "WenQuanYi Micro Hei:size=9.5"
    
};

static const char dmenufont[] = "monospace-11";

static const unsigned int borderpx  = 1;        	/* border pixel of windows */
static const unsigned int gappx     = 10;           /* gap pixel between windows */
static const unsigned int snap      = 32;       	/* snap pixel */
static const unsigned int systraypinning = 0;   	/* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 0;   	/* systray spacing */
static const Bool systraypinningfailfirst = True;   /* True: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const Bool showsystray       = True;     	/* False means no systray */
static const Bool topbar            = True;     	/* False means bottom bar */
static const Bool resizehints 		= False; 		/* True means respect size hints in tiled resizals */

static const char colors[NUMCOLORS][MAXCOLORS][8] = {
  /* border  foreground background */
  { "#3f3f3f", "#dddddd", "#3f3f3f" },  /* norm */
  { "#ff0000", "#dcdccc", "#506070" },  /* sel  */
  { "#dcdccc", "#dcdccc", "#ff9999" },
  { "#dcdccc", "#dcdccc", "#ffff99" },
  { "#dcdccc", "#dcdccc", "#add6ff" },
  { "#dcdccc", "#dcdccc", "#ebc2ff" },
  { "#dcdccc", "#dcdccc", "#ff99c2" },
};

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "google-chrome-stable",NULL,       NULL,       1 << 1,       	False,       -1 },
	{ "termite",         NULL,       NULL,       1 << 2,       	False,        -1 },
	{ "Pcmanfm",         NULL,       NULL,       1 << 3,       	False,        -1 },
	{ "Vlc", 	         NULL,       NULL,       1 << 4,       False,        -1 },
};

/* tagging */
static const Tag tags[] = { 
	/* Name	Layout	mfact      nmaster showbar*/
	{ "\uff5e",  0,      MFACTOR,   1,      False  },
	{ "web",  0,      MFACTOR,   1,      True  },
	{ "term",  0,      MFACTOR,   1,      True  },
	{ "file",  0,      MFACTOR,   1,      True  },
	{ "media",  0,      MFACTOR,   1,      True  },
	{ "misc",  0,      MFACTOR,   1,      True  },
	{ "\uff16",  0,      MFACTOR,   1,      True  },
	{ "\uff17",  0,      MFACTOR,   1,      True  },
	{ "\uff38",  0,      MFACTOR,   1,      True  },
	{ "\uff26",  0,      MFACTOR,   1,      True  },
	{ "\uff10",  0,      MFACTOR,   1,      True  },
	{ "\uff37",  0,      MFACTOR,   1,      True  },
	{ "\uff1d",  0,      MFACTOR,   1,      True  },
};

/* layouts */
#include "gaplessgrid.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	/* first entry is default */
    { "[F]",      tile },    
	{ "[T]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[#]",      gaplessgrid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", colors[0][1], "-nf", colors[0][0], "-sb", colors[0][0], "-sf", colors[0][1], NULL };

static const char *termcmd[]  = { "termite", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_z,      zoomcycle,      {0} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_BackSpace, view,        {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_BackSpace, tag,         {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_quoteleft,		       0)
	TAGKEYS(                        XK_1,                      1)
	TAGKEYS(                        XK_2,                      2)
	TAGKEYS(                        XK_3,                      3)
	TAGKEYS(                        XK_4,                      4)
	TAGKEYS(                        XK_5,                      5)
	TAGKEYS(                        XK_6,                      6)
	TAGKEYS(                        XK_7,                      7)
	TAGKEYS(                        XK_8,                      8)
	TAGKEYS(                        XK_9,                      9)
	TAGKEYS(                        XK_0,                      10)
	TAGKEYS(                        XK_minus,                  11)
	TAGKEYS(                        XK_equal,                  12)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
 	{ MODKEY,                       XK_Left,   xadjtag,    	   {.i = -1 } },
 	{ MODKEY,                       XK_Right,  xadjtag,		   {.i = +1 } },
    { MODKEY|ControlMask,           XK_j,      pushdown,       {0} },
    { MODKEY|ControlMask,           XK_k,      pushup,         {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

struct Pertag 
{
	unsigned int curtag;
	int nmasters[LENGTH(tags) + 1];
	float mfacts[LENGTH(tags) + 1];
	unsigned int sellts[LENGTH(tags) + 1];
	const Layout *ltidxs[LENGTH(tags) + 1][2];
	Bool showbars[LENGTH(tags) + 1];
	Client *prevzooms[LENGTH(tags) + 1];
};

