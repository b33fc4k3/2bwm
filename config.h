// SEE ALSO: https://github.com/yrmt/dotfiles/blob/master/2bwm.conf
// SEE ALSO: http://pastebin.com/aNKYQtHk
// SEE ALSO: http://git.z3bra.org/cgit.cgi/2bwm/tree/
// SEE ALSO: http://www.reddit.com/r/unixporn/comments/1wge5f/arch2bwm_bring_your_terminal_to_the_next_level/
// style: http://ybeastie.deviantart.com/art/FreeBSD-and-Mcwm-beast-364293840
// colors inverted
// inner ährm ... now outer border way thinner than now inner ... now outer just plain black
///---User configurable stuff---///

// strcat()
//#define MY_PATH "/home/marten/"
//#define CAT(a, b) a ## b
//int main( void )
//{
//    printf("%s", CAT(MY_PATH, "scripts/dmenu"));
//    return 0;
//}

///---Modifiers---///
#define MOD             XCB_MOD_MASK_4       /* Super/Windows key  or check xmodmap(1) with -pm*/
///--Speed---///
/* Move this many pixels when moving or resizing with keyboard unless the window has hints saying otherwise.
 *0)move step slow   1)move step fast
 *2)mouse slow       3)mouse fast     */
static const uint16_t movements[] = {10,40,15,450};
/* resize by line like in mcwm -- jjumbi */
static const bool     resize_by_line          = true;
/* the ratio used when resizing and keeping the aspect */
static const float    resize_keep_aspect_ratio= 1.03;
///---Offsets---///
/*0)offsetx          1)offsety
 *2)maxwidth         3)maxheight */
//static const uint8_t offsets[] = {0,0,0,0};
//static const uint8_t offsets[] = {20,20,40,40};
// TODO kein snap to borders mehr ... nervt
static const uint8_t offsets[] = {20,20,40,40};
///---Colors---///
/*0)focuscol         1)unfocuscol
 *2)fixedcol         3)unkilcol
 *4)fixedunkilcol    5)outerbordercol
 *6)emptycol         */
// http://www.w3schools.com/html/html_colors.asp
//                                focus     unfocus   fixed     unkill    fixunkil  outerbor  empty
// for inverted colors = true
//static const char *colors[] = {"#323232","#191919","#4c5739","#682a2a","#604818","#151515","#222222"};

// for inverted colors = false
static const char *colors[] = {"#404040","#282828","#4c5739","#682a2a","#604818","#000000","#222222"}; // ybeastie-like
//static const char *colors[] = {"#35586c","#333333","#7a8c5c","#ff6666","#cc9933","#0d131a","#000000"}; // crap std but blue outer border
//static const char *colors[] = {"#1c678c","#44484c","#7a8c5c","#ff6666","#cc9933","#0d131a","#000000"};
/* if this is set to true the inner border and outer borders colors will be swapped */
static const bool inverted_colors = false;
//static const bool inverted_colors = true;
///---Borders---///
/*0) Outer border size. If you put this negative it will be a square.
 *1) Full borderwidth    2) Magnet border size    
 *3) Resize border size  */
//static const uint8_t borders[] = {2,5,9,9};
// outer border = marking color toggling fixing
// full border  = outer plus ?
//static const uint8_t borders[] = {5,10,50,30};
static const uint8_t borders[] = {2,10,5,30}; // ybeastie like
/* Windows that won't have a border.*/
#define LOOK_INTO "_NET_WM_NAME"
//static const char *ignore_names[] = {"bar"};
static const char *ignore_names[] = {"bar", "chromium-browser", "browser"};
///--Menus and Programs---///
// what to do with this my_menu thing !?
// also run-or-raise stumpwm like for emacs and all sorts
static const char *menucmd[]   = { "/usr/bin/my_menu.sh", NULL };
static const char *run9menustart[]   = { "/home/marten/scripts/9main.sh /home/marten/scripts/menu1.txt", NULL };
static const char *gmrun[]     = { "/usr/bin/gmrun",NULL};
//static const char *terminal[]  = { "urxvtc", NULL };
static const char *terminal[]  = { "urxvt", NULL };
// MARTEN
//static const char *dmenu[]  = { "/home/marten/scripts/dmenu_run_dark", NULL };
static const char *dmenu[]  = { "/home/marten/scripts/dmenu_run_dark", NULL };
static const char *lock[]  = { "xtrlock", NULL };
///--Custom foo---///
static void halfandcentered(const Arg *arg)
{
	Arg arg2 = {.i=2};
	maxhalf(&arg2);
	Arg arg3 = {.i=0};
	teleport(&arg3);
}
///---Shortcuts---///
/* Check /usr/include/X11/keysymdef.h for the list of all keys
 * For AZERTY keyboards XK_1...0 should be replaced by :
 *      DESKTOPCHANGE(     XK_ampersand,                     0)
 *      DESKTOPCHANGE(     XK_eacute,                        1)
 *      DESKTOPCHANGE(     XK_quotedbl,                      2)
 *      DESKTOPCHANGE(     XK_apostrophe,                    3)
 *      DESKTOPCHANGE(     XK_parenleft,                     4)
 *      DESKTOPCHANGE(     XK_minus,                         5)
 *      DESKTOPCHANGE(     XK_egrave,                        6)
 *      DESKTOPCHANGE(     XK_underscore,                    7)
 *      DESKTOPCHANGE(     XK_ccedilla,                      8)
 *      DESKTOPCHANGE(     XK_agrave,                        9)*
 */
#define DESKTOPCHANGE(K,N) \
{  MOD ,             K,              changeworkspace, {.i=N}}, \
{  MOD |SHIFT,       K,              sendtoworkspace, {.i=N}},
static key keys[] = {
    /* modifier           key            function           argument */
    // Focus to next/previous window
    {  MOD ,              XK_Tab,        focusnext,         {.i=0}},
    {  MOD |SHIFT,        XK_Tab,        focusnext,         {.i=1}},
    // Kill a window
    {  MOD ,              XK_q,          deletewin,         {.i=0}},
    // Resize a window
    {  MOD |SHIFT,        XK_k,          resizestep,        {.i=2}},
    {  MOD |SHIFT,        XK_j,          resizestep,        {.i=1}},
    {  MOD |SHIFT,        XK_l,          resizestep,        {.i=3}},
    {  MOD |SHIFT,        XK_h,          resizestep,        {.i=0}},
    // Resize a window slower
    {  MOD |SHIFT|CONTROL,XK_k,          resizestep,        {.i=6}},
    {  MOD |SHIFT|CONTROL,XK_j,          resizestep,        {.i=5}},
    {  MOD |SHIFT|CONTROL,XK_l,          resizestep,        {.i=7}},
    {  MOD |SHIFT|CONTROL,XK_h,          resizestep,        {.i=4}},
    // Move a window
    {  MOD ,              XK_k,          movestep,          {.i=2}},
    {  MOD ,              XK_j,          movestep,          {.i=1}},
    {  MOD ,              XK_l,          movestep,          {.i=3}},
    {  MOD ,              XK_h,          movestep,          {.i=0}},
    // Move a window slower
    {  MOD |CONTROL,      XK_k,          movestep,          {.i=6}},
    {  MOD |CONTROL,      XK_j,          movestep,          {.i=5}},
    {  MOD |CONTROL,      XK_l,          movestep,          {.i=7}},
    {  MOD |CONTROL,      XK_h,          movestep,          {.i=4}},
    // Teleport the window to an area of the screen.
    // Center:
    {  MOD ,              XK_g,          teleport,          {.i=0}},
    // Center y:
    {  MOD |SHIFT,        XK_g,          teleport,          {.i=3}},
    // Center x:
    {  MOD |CONTROL,      XK_g,          teleport,          {.i=-3}},
    // Top left:
    {  MOD ,              XK_y,          teleport,          {.i=2}},
    // Top right:
    {  MOD ,              XK_u,          teleport,          {.i=-2}},
    // Bottom left:
    {  MOD ,              XK_b,          teleport,          {.i=1}},
    // Bottom right:
    {  MOD ,              XK_n,          teleport,          {.i=-1}},
    // Resize while keeping the window aspect
    {  MOD ,              XK_Home,       resizestep_aspect, {.i=0}},
    {  MOD ,              XK_End,        resizestep_aspect, {.i=1}},
    // Full screen window without borders
    {  MOD ,              XK_x,         maximize,          {.i=0}},
    //Full screen window without borders overiding offsets
    // FLASH trick ... yay ... offsets and video fine ^^
    {  MOD |SHIFT ,       XK_x,          maximize,          {.i=1}},
    // Maximize vertically
    {  MOD ,              XK_m,          maxvert_hor,       {.i=1}},
    // Maximize horizontally
    {  MOD |SHIFT,        XK_m,          maxvert_hor,       {.i=0}},
    // Maximize and move
    // vertically left
    {  MOD |SHIFT,        XK_y,          maxhalf,           {.i=2}},
    // vertically right
    {  MOD |SHIFT,        XK_u,          maxhalf,           {.i=1}},
    // horizontally left
    {  MOD |SHIFT,        XK_b,          maxhalf,           {.i=-1}},
    // horizontally right
    {  MOD |SHIFT,        XK_n,          maxhalf,           {.i=-2}},
    //fold half vertically
    {  MOD |SHIFT|CONTROL,XK_y,          maxhalf,           {.i=4}},
    //fold half horizontally
    {  MOD |SHIFT|CONTROL,XK_b,          maxhalf,           {.i=-4}},
    //unfold vertically
    {  MOD |SHIFT|CONTROL,XK_u,          maxhalf,           {.i=3}},
    //unfold horizontally
    {  MOD |SHIFT|CONTROL,XK_n,          maxhalf,           {.i=-3}},
    // Next/Previous screen
    {  MOD ,              XK_comma,      changescreen,      {.i=1}},
    {  MOD ,              XK_period,     changescreen,      {.i=0}},
    // Raise or lower a window
    {  MOD ,              XK_r,          raiseorlower,      {.i=0}},
    // Next/Previous workspace
    {  MOD ,              XK_v,          nextworkspace,     {.i=0}},
    {  MOD ,              XK_c,          prevworkspace,     {.i=0}},
    // Iconify the window
    {  MOD ,              XK_i,          hide,              {.i=0}},
    // Make the window unkillable
    {  MOD ,              XK_a,          unkillable,        {.i=0}},
    // Make the window appear always on top
    {  MOD,               XK_t,          always_on_top,     {.i=0}},
    // Make the window stay on all workspaces
    {  MOD ,              XK_f,          fix,               {.i=0}},
    // Move the cursor
    {  MOD ,              XK_Up,         cursor_move,       {.i=4}},
    {  MOD ,              XK_Down,       cursor_move,       {.i=5}},
    {  MOD ,              XK_Right,      cursor_move,       {.i=6}},
    {  MOD ,              XK_Left,       cursor_move,       {.i=7}},
    // Move the cursor faster
    {  MOD |SHIFT,        XK_Up,         cursor_move,       {.i=0}},
    {  MOD |SHIFT,        XK_Down,       cursor_move,       {.i=1}},
    {  MOD |SHIFT,        XK_Right,      cursor_move,       {.i=2}},
    {  MOD |SHIFT,        XK_Left,       cursor_move,       {.i=3}},
    // Start programs
    {  MOD ,              XK_Return,     start,             {.com = terminal}},
    {  MOD ,              XK_w,          start,             {.com = menucmd}},
    {  MOD |SHIFT,        XK_w,          start,             {.com = gmrun}},
    {  MOD ,              XK_p,          start,             {.com = dmenu}},
    {  MOD |SHIFT,        XK_e,          start,             {.com = lock}},
    {  MOD |CONTROL,      XK_s,          start,             {.com = run9menustart}},
    // Exit or restart 2bwm
    {  MOD |CONTROL,      XK_q,          twobwm_exit,         {.i=0}},
    {  MOD |CONTROL,      XK_r,          twobwm_restart,      {.i=0}},
    {  MOD ,              XK_space,      halfandcentered,    {.i=0}},
    // Change current workspace
       DESKTOPCHANGE(     XK_1,                             0)
       DESKTOPCHANGE(     XK_2,                             1)
       DESKTOPCHANGE(     XK_3,                             2)
       DESKTOPCHANGE(     XK_4,                             3)
       DESKTOPCHANGE(     XK_5,                             4)
       DESKTOPCHANGE(     XK_6,                             5)
       DESKTOPCHANGE(     XK_7,                             6)
       DESKTOPCHANGE(     XK_8,                             7)
       DESKTOPCHANGE(     XK_9,                             8)
       DESKTOPCHANGE(     XK_0,                             9)
};
static Button buttons[] = {
    {  MOD        ,XCB_BUTTON_INDEX_1,     mousemotion,   {.i=TWOBWM_MOVE}},
    {  MOD        ,XCB_BUTTON_INDEX_3,     mousemotion,   {.i=TWOBWM_RESIZE}},
    {  MOD|CONTROL,XCB_BUTTON_INDEX_3,     start,         {.com = menucmd}},
    {  MOD|SHIFT,  XCB_BUTTON_INDEX_1,     changeworkspace, {.i=0}},
    {  MOD|SHIFT,  XCB_BUTTON_INDEX_3,     changeworkspace, {.i=1}},
    {  MOD|ALT,    XCB_BUTTON_INDEX_1,     changescreen,    {.i=1}},
    {  MOD|ALT,    XCB_BUTTON_INDEX_3,     changescreen,    {.i=0}}
};
