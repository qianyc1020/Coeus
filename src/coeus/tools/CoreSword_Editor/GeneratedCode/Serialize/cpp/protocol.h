// Generate by the sword of core(核心之刃). DO NOT EDIT!
// Source : Protocol.h
// Comment : 在此处输入注释...

#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include <venus_net/common.h>
#include <venus_net/basic_stream.h>
#include <venus_net/stream_reader.h>
#include <venus_net/stream_writer.h>
#include <venus_net/network_common.h>

namespace GameEncoder
{
    static int32 getStrListSize(const std::vector<std::string>& strList) 
    {
        int32 size = 0; 
        for (int32 i = 0; i < strList.size(); i++) 
        { 
            size += strList[i].length() + 2; 
        }

        return size + 2;
    }

    template<class T> 
    static int32 getStructArrBytesSize(const std::vector<T>& vt)
    {
        int32 size = 0; 
        for (int32 i = 0; i < vt.size(); i++) 
        { 
            size += vt[i].byteSize(); 
        }

        return 2 + size;
    }

    //角色基本数据
    struct CharacterInitialData 
    {
        std::string nickname;                   //角色昵称
        uint8 character_type;             //角色类型（职业）
        int32 hp;                         //生命值
        int32 max_hp;                     //最大生命值
        int32 exp;                        //经验值
        int32 next_exp;                   //升级需要的经验值
        uint32 power;                      //战斗力
        uint16 level;                      //等级

        int32 byteSize()
        {
            return (nickname.length() + 2) + sizeof(character_type) + sizeof(hp) + sizeof(max_hp) + sizeof(exp) + sizeof(next_exp) + sizeof(power) + sizeof(level);
        }

    };

    static StreamReader& operator >> (StreamReader& r, CharacterInitialData& st)
    {
        r >> st.nickname;
        r >> st.character_type;
        r >> st.hp;
        r >> st.max_hp;
        r >> st.exp;
        r >> st.next_exp;
        r >> st.power;
        r >> st.level;

        return r;
    }

    static StreamWriter& operator << (StreamWriter& w, CharacterInitialData& st)
    {
        w << st.nickname;
        w << st.character_type;
        w << st.hp;
        w << st.max_hp;
        w << st.exp;
        w << st.next_exp;
        w << st.power;
        w << st.level;

        return w;
    }

    struct Epic 
    {
        uint8 family_type;                //家庭背景
        uint8 story_type;                 //我的故事
        uint32 characteristic;

        int32 byteSize()
        {
            return sizeof(family_type) + sizeof(story_type) + sizeof(characteristic);
        }

    };

    static StreamReader& operator >> (StreamReader& r, Epic& st)
    {
        r >> st.family_type;
        r >> st.story_type;
        r >> st.characteristic;

        return r;
    }

    static StreamWriter& operator << (StreamWriter& w, Epic& st)
    {
        w << st.family_type;
        w << st.story_type;
        w << st.characteristic;

        return w;
    }

    struct PlayerFullData 
    {
        uint64 userid;
        uint64 character_id;
        uint8 character_type;
        std::string nickname;
        uint8 gender;
        Epic epic;
        int64 last_login;
        CharacterInitialData initial_data;

        int32 byteSize()
        {
            return sizeof(userid) + sizeof(character_id) + sizeof(character_type) + (nickname.length() + 2) + sizeof(gender) + epic.byteSize() + sizeof(last_login) + initial_data.byteSize();
        }

    };

    static StreamReader& operator >> (StreamReader& r, PlayerFullData& st)
    {
        r >> st.userid;
        r >> st.character_id;
        r >> st.character_type;
        r >> st.nickname;
        r >> st.gender;
        r >> st.epic;
        r >> st.last_login;
        r >> st.initial_data;

        return r;
    }

    static StreamWriter& operator << (StreamWriter& w, PlayerFullData& st)
    {
        w << st.userid;
        w << st.character_id;
        w << st.character_type;
        w << st.nickname;
        w << st.gender;
        w << st.epic;
        w << st.last_login;
        w << st.initial_data;

        return w;
    }

    /**
    * ● 登录&注册(4 message)
    */

    //登录请求
    struct CSLoginReq : public NetworkMessage
    {
        //登录帐号（邮箱地址）
        std::string account;
        //密码
        std::string password;

        int32 byteSize()
        {
            return (account.length() + 2) + (password.length() + 2);
        }

        void encode(byte* buffer, int32 size)
        {
            StreamWriter w(buffer, size);
            w << account;
            w << password;
        }

        void decode(const byte* buffer, int32 size)
        {
            StreamReader r(buffer, size);
            r >> account;
            r >> password;
        }
    };

    //登录返回
    struct SCLoginRsp : public NetworkMessage
    {
        //登录结果
        uint8 login_result;
        //角色ID
        uint64 player_id;
        //是否需要创建角色
        uint8 character_create_require;

        int32 byteSize()
        {
            return sizeof(login_result) + sizeof(player_id) + sizeof(character_create_require);
        }

        void encode(byte* buffer, int32 size)
        {
            StreamWriter w(buffer, size);
            w << login_result;
            w << player_id;
            w << character_create_require;
        }

        void decode(const byte* buffer, int32 size)
        {
            StreamReader r(buffer, size);
            r >> login_result;
            r >> player_id;
            r >> character_create_require;
        }
    };

    //用户注册请求
    struct CSRegisterReq : public NetworkMessage
    {
        //要注册的用户名
        std::string username;
        //密码
        std::string password;

        int32 byteSize()
        {
            return (username.length() + 2) + (password.length() + 2);
        }

        void encode(byte* buffer, int32 size)
        {
            StreamWriter w(buffer, size);
            w << username;
            w << password;
        }

        void decode(const byte* buffer, int32 size)
        {
            StreamReader r(buffer, size);
            r >> username;
            r >> password;
        }
    };

    //用户注册返回
    struct SCRegisterRsp : public NetworkMessage
    {
        //注册结果（true-成功， false-失败）
        uint8 register_result;

        int32 byteSize()
        {
            return sizeof(register_result);
        }

        void encode(byte* buffer, int32 size)
        {
            StreamWriter w(buffer, size);
            w << register_result;
        }

        void decode(const byte* buffer, int32 size)
        {
            StreamReader r(buffer, size);
            r >> register_result;
        }
    };

    /**
    * ● 角色创建(4 message)
    */

    //发送创建角色的请求
    struct CSCreateCharacter : public NetworkMessage
    {
        //昵称
        std::string nickname;
        //性别
        uint8 gender;
        //角色类型（职业）
        uint8 character_type;
        //我的史诗
        Epic epic;

        int32 byteSize()
        {
            return (nickname.length() + 2) + sizeof(gender) + sizeof(character_type) + epic.byteSize();
        }

        void encode(byte* buffer, int32 size)
        {
            StreamWriter w(buffer, size);
            w << nickname;
            w << gender;
            w << character_type;
            w << epic;
        }

        void decode(const byte* buffer, int32 size)
        {
            StreamReader r(buffer, size);
            r >> nickname;
            r >> gender;
            r >> character_type;
            r >> epic;
        }
    };

    //创建角色返回
    struct SCCreateCharacter : public NetworkMessage
    {
        //结果
        uint8 result;

        int32 byteSize()
        {
            return sizeof(result);
        }

        void encode(byte* buffer, int32 size)
        {
            StreamWriter w(buffer, size);
            w << result;
        }

        void decode(const byte* buffer, int32 size)
        {
            StreamReader r(buffer, size);
            r >> result;
        }
    };

    //请求检查昵称是否存在
    struct CSCheckNicknameExist : public NetworkMessage
    {
        //昵称
        std::string nickname;

        int32 byteSize()
        {
            return (nickname.length() + 2);
        }

        void encode(byte* buffer, int32 size)
        {
            StreamWriter w(buffer, size);
            w << nickname;
        }

        void decode(const byte* buffer, int32 size)
        {
            StreamReader r(buffer, size);
            r >> nickname;
        }
    };

    //返回昵称检查结果
    struct SCCheckNicknameExist : public NetworkMessage
    {
        //结果
        uint8 result;

        int32 byteSize()
        {
            return sizeof(result);
        }

        void encode(byte* buffer, int32 size)
        {
            StreamWriter w(buffer, size);
            w << result;
        }

        void decode(const byte* buffer, int32 size)
        {
            StreamReader r(buffer, size);
            r >> result;
        }
    };

    /**
    * ● 系统(2 message)
    */

    //错误通知
    struct SCErrorNotify : public NetworkMessage
    {
        //错误码
        uint32 error_code;

        int32 byteSize()
        {
            return sizeof(error_code);
        }

        void encode(byte* buffer, int32 size)
        {
            StreamWriter w(buffer, size);
            w << error_code;
        }

        void decode(const byte* buffer, int32 size)
        {
            StreamReader r(buffer, size);
            r >> error_code;
        }
    };

    //扩展的错误通知
    struct SCErrorExNotify : public NetworkMessage
    {
        //错误码
        uint32 error_code;
        //错误原因
        std::string reason;

        int32 byteSize()
        {
            return sizeof(error_code) + (reason.length() + 2);
        }

        void encode(byte* buffer, int32 size)
        {
            StreamWriter w(buffer, size);
            w << error_code;
            w << reason;
        }

        void decode(const byte* buffer, int32 size)
        {
            StreamReader r(buffer, size);
            r >> error_code;
            r >> reason;
        }
    };

    /**
    * ● 角色属性(2 message)
    */

    //请求玩家初始数据
    struct CSCharacterInitialDataReq : public NetworkMessage
    {

        int32 byteSize()
        {
            return 0;
        }

        void encode(byte* buffer, int32 size)
        {
        }

        void decode(const byte* buffer, int32 size)
        {
        }
    };

    //玩家属性返回
    struct SCCharacterInitialDataRsp : public NetworkMessage
    {
        CharacterInitialData char_initial_data;

        int32 byteSize()
        {
            return char_initial_data.byteSize();
        }

        void encode(byte* buffer, int32 size)
        {
            StreamWriter w(buffer, size);
            w << char_initial_data;
        }

        void decode(const byte* buffer, int32 size)
        {
            StreamReader r(buffer, size);
            r >> char_initial_data;
        }
    };

    /**
    * ● 在线聊天(5 message)
    */

    //发送公共聊天
    struct CSSendPublicChatMessageReq : public NetworkMessage
    {
        //频道
        uint8 channel;
        //聊天内容
        std::string message;

        int32 byteSize()
        {
            return sizeof(channel) + (message.length() + 2);
        }

        void encode(byte* buffer, int32 size)
        {
            StreamWriter w(buffer, size);
            w << channel;
            w << message;
        }

        void decode(const byte* buffer, int32 size)
        {
            StreamReader r(buffer, size);
            r >> channel;
            r >> message;
        }
    };

    //发送私聊消息（通过GUID）
    struct CSSendPrivateChatMessageByIdReq : public NetworkMessage
    {
        //目标玩家ID
        uint64 target_id;
        //聊天内容
        std::string message;

        int32 byteSize()
        {
            return sizeof(target_id) + (message.length() + 2);
        }

        void encode(byte* buffer, int32 size)
        {
            StreamWriter w(buffer, size);
            w << target_id;
            w << message;
        }

        void decode(const byte* buffer, int32 size)
        {
            StreamReader r(buffer, size);
            r >> target_id;
            r >> message;
        }
    };

    //发送私聊消息（通过昵称）
    struct CSSendPrivateChatMessageByNameReq : public NetworkMessage
    {
        //目标玩家昵称
        std::string target_name;
        //聊天内容
        std::string message;

        int32 byteSize()
        {
            return (target_name.length() + 2) + (message.length() + 2);
        }

        void encode(byte* buffer, int32 size)
        {
            StreamWriter w(buffer, size);
            w << target_name;
            w << message;
        }

        void decode(const byte* buffer, int32 size)
        {
            StreamReader r(buffer, size);
            r >> target_name;
            r >> message;
        }
    };

    //公共聊天消息通知
    struct SCPublicChatMessageNotification : public NetworkMessage
    {
        //频道
        uint8 channel;
        //聊天内容
        std::string message;

        int32 byteSize()
        {
            return sizeof(channel) + (message.length() + 2);
        }

        void encode(byte* buffer, int32 size)
        {
            StreamWriter w(buffer, size);
            w << channel;
            w << message;
        }

        void decode(const byte* buffer, int32 size)
        {
            StreamReader r(buffer, size);
            r >> channel;
            r >> message;
        }
    };

    //私聊消息通知
    struct SCPrivateChatMessageNotification : public NetworkMessage
    {
        //目标玩家ID
        uint64 target_id;
        //目标玩家昵称
        std::string target_name;
        //聊天内容
        std::string message;

        int32 byteSize()
        {
            return sizeof(target_id) + (target_name.length() + 2) + (message.length() + 2);
        }

        void encode(byte* buffer, int32 size)
        {
            StreamWriter w(buffer, size);
            w << target_id;
            w << target_name;
            w << message;
        }

        void decode(const byte* buffer, int32 size)
        {
            StreamReader r(buffer, size);
            r >> target_id;
            r >> target_name;
            r >> message;
        }
    };

}

#endif    //__PROTOCOL_H__