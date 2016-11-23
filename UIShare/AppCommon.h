#ifndef APPCOMMON_H
#define APPCOMMON_H

enum MenuCmdId
{
    CMDID_MENU_FM=101,
    CMDID_MENU_TEL,
    CMDID_MENU_MSG,
    CMDID_MENU_CD,
    CMDID_MENU_LIST
};


enum ShowType
{
    ID_APPLINK = 0,
    ID_CHOICESET,
    ID_COMMAND,
    ID_SHOW,
    ID_ALERT,
    ID_AUDIOPASSTHRU,
    ID_CHOICESETVR,
    ID_SCROLLMSG,
    ID_SLIDER,
    ID_NOTIFY,
    ID_MEDIACLOCK,    
    ID_VIDEOSTREAM,
    ID_MAIN,
    ID_UI_MAX
};


#define MIN_APP_BASE  ID_APPLINK
#define MAX_APP_BASE  (ID_SHOW+1)
#define MIN_POP_BASE  ID_ALERT
#define MAX_POP_BASE  (ID_APP_MAX)
enum VRID
{
    ID_DEFAULT = 0,
    ID_CANCEL,
    ID_HELP,
    ID_EXIT,
    ID_SWITCHAPP
};

typedef enum
{
    ID_CHN_BUTTON=0,
    ID_CHN_TTS,
    ID_CHN_VR,
    ID_CHN_BASE,
    ID_CHN_UI,
    ID_CHN_VEHICLE,
    ID_CHN_NAVI,
    ID_CHN_MAX
}ID_CHN_TYPE;

enum RESULT_CODE
{
    RESULT_SUCCESS=0,
    RESULT_UNSUPPORTED_REQUEST= 1,
    RESULT_UNSUPPORTED_RESOURCE= 2,
    RESULT_DISALLOWED= 3,
    RESULT_REJECTED= 4,
    RESULT_ABORTED= 5,
    RESULT_IGNORED= 6,
    RESULT_RETRY= 7,
    RESULT_IN_USE= 8,
    RESULT_DATA_NOT_AVAILABLE= 9,
    RESULT_TIMED_OUT= 10,
    RESULT_INVALID_DATA= 11,
    RESULT_CHAR_LIMIT_EXCEEDED= 12,
    RESULT_INVALID_ID= 13,
    RESULT_DUPLICATE_NAME= 14,
    RESULT_APPLICATION_NOT_REGISTERED= 15,
    RESULT_WRONG_LANGUAGE= 16,
    RESULT_OUT_OF_MEMORY= 17,
    RESULT_TOO_MANY_PENDING_REQUESTS= 18,
    RESULT_NO_APPS_REGISTERED= 19,
    RESULT_NO_DEVICES_CONNECTED= 20,
    RESULT_WARNINGS= 21,
    RESULT_GENERIC_ERROR= 22,
    RESULT_USER_DISALLOWED= 23,
    RESULT_USER_WAIT//user added
};

typedef RESULT_CODE  Result;

enum RPC_TYPE
{
    RPC_Show=0,
    RPC_Alert,
    RPC_ScrollMessage,
    RPC_Slider,
    RPC_PerformAudioPassthru,
    RPC_PerformInteraction,
    RPC_StartStream,
    RPC_StopStream,
    RPC_SetMediaClockTimer,
    RPC_MAX
};

#endif // APPCOMMON_H

