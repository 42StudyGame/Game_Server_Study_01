using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace csharp_test_client
{
    class PacketDef
    {
        public const Int16 PACKET_HEADER_SIZE = 5;
        public const int MAX_USER_ID_BYTE_LENGTH = 16;
        public const int MAX_USER_PW_BYTE_LENGTH = 16;
        public const int MAX_ROOM_CHAT_MSG_SIZE = 256;
    }

    public enum PACKET_ID : ushort
    {
        // 로그인
        PK_LOGIN_REQ = 21,
        PK_LOGIN_RES = 22,

        PK_ENTER_ROOM_REQ = 61,
        PK_ENTER_ROOM_RES = 62,        
        PK_NEW_USER_ENTER_ROOM_NTF = 63,
        //ROOM_USER_LIST_NTF = 64,

        PK_LEAVE_ROOM_REQ = 66,
        PK_LEAVE_ROOM_RES = 67,
        PK_USER_LEAVE_ROOM_NTF = 68,

        PK_CHAT_ROOM_REQ = 76,
        PK_CHAT_ROOM_RES = 77,
        PK_CHAT_ROOM_NTF = 78,



        //PACKET_ID_ERROR_NTF = 703,

        // Ping(Heart-beat)
        //PING_REQ = 706,
        //PING_RES = 707,

        //PACKET_ID_ROOM_RELAY_REQ = 741,
        //PACKET_ID_ROOM_RELAY_NTF = 742,
    }


    public enum ERROR_CODE : Int16
    {
        ERROR_NONE = 0,



        ERROR_CODE_USER_MGR_INVALID_USER_UNIQUEID = 112,

        ERROR_CODE_PUBLIC_CHANNEL_IN_USER = 114,

        ERROR_CODE_PUBLIC_CHANNEL_INVALIDE_NUMBER = 115,
    }
}
