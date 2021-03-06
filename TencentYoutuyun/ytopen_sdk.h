#ifndef _YTOPEN_SDK_
#define _YTOPEN_SDK_
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <curl/curl.h>
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/document.h"
#include "bin2ascii.h"
#include "sign/include/qcloud_sign.h"

class ytopen_sdk
{
    public:
        typedef struct AppSign
        {
            uint32_t app_id;
            std::string secret_id;
            std::string secret_key;
            std::string user_id;
        }AppSign;

        enum Domain
        {
            API_YOUTU_END_POINT = 0,
            API_FACE_IN_YOUTU_END_POINT = 2
        };

    public:

        /**
         * @brief Init
         * @param t_app_sign 密钥身份信息
         * @param domain 服务的域名地址
         */

        void Init(const AppSign& t_app_sign, Domain domain = API_YOUTU_END_POINT);

        /**
         * @brief DetectFace
         * @param result Json格式的请求结果
         * @param imagePath 待检测的图片数据本地路径／url
         * @param data_type 图片数据类型 图片本地路径／url 0／1
         * @param isBigFace 是否大脸模式
         * @return 0成功 -1失败
         */
        int DetectFace(rapidjson::Document &result, const std::string& imagePath, int data_type = 0, bool isBigFace = false);

        /**
         * @brief FaceShape
         * @param result Json格式的请求结果
         * @param imagePath 待检测的图片数据本地路径／url
         * @param data_type 图片数据类型 图片本地路径／url 0／1
         * @param isBigFace 是否大脸模式
         * @return 0成功 -1失败
         */
        int FaceShape(rapidjson::Document &result, const std::string& imagePath, int data_type = 0, bool isBigFace = false);

        /**
         * @brief FaceCompare
         * @param result Json格式的请求结果
         * @param imagePathA 待比对的A图片本地路径／url
         * @param imagePathB 待比对的A图片本地路径／url
         * @param data_type 图片数据类型 图片本地路径／url 0／1
         * @return 0成功 -1失败
         */
        int FaceCompare(rapidjson::Document &result, const std::string& imagePathA, const std::string&imagePathB, int data_type = 0);

        /**
         * @brief FaceVerify
         * @param result Json格式的请求结果
         * @param person_id 待验证的人脸id
         * @param imagePath 待验证的图片本地路径／url
         * @param data_type 图片数据类型 图片本地路径／url 0／1
         * @return 0成功 -1失败
         */
        int FaceVerify(rapidjson::Document &result, const std::string& person_id, const std::string& imagePath, int data_type = 0);

        /**
         * @brief FaceIdentify
         * @param result Json格式的请求结果
         * @param group_id 识别的组id
         * @param imagePath 待识别的图片本地路径／url
         * @param data_type 图片数据类型 图片本地路径／url 0／1
         * @return 0成功 -1失败
         */
        int FaceIdentify(rapidjson::Document &result, const std::string& group_id, const std::string& imagePath, int data_type = 0);

        /**
         * @brief MultiFaceIdentify
         * @param result Json格式的请求结果
         * @param group_id 识别的组id
         * @param group_ids 识别的个体存放的组id，可以指定多个组id，用户指定（组默认创建）
         * @param imagePath 待识别的图片本地路径／url
         * @param data_type 图片数据类型 图片本地路径／url 0／1
         * @param topn 候选人脸数量，一般使用默认值5
         * @param min_size 人脸检测最小尺寸，一般使用默认值40
         * @return 0成功 -1失败
         */
        int MultiFaceIdentify(rapidjson::Document &result, const std::string& group_id, const std::vector<std::string> &group_ids, const std::string& imagePath, int data_type = 0, int topn = 5, int min_size = 40);

        /**
         * @brief NewPerson
         * @param result Json格式的请求结果
         * @param person_id 新建的个体id，用户指定，需要保证app_id下的唯一性
         * @param person_name 个体姓名
         * @param group_ids 新建的个体存放的组id，可以指定多个组id，用户指定（组默认创建）
         * @param imagePath 包含个体人脸的图片本地路径／url
         * @param data_type 图片数据类型 图片本地路径／url 0／1
         * @param tag 备注信息，用户自解释字段
         * @return 0成功 -1失败
         */
        int NewPerson(rapidjson::Document &result, const std::string& person_id, const std::string &person_name, const std::vector<std::string> &group_ids, const std::string& imagePath, int data_type = 0, const std::string &tag = "");

        /**
         * @brief DelPerson
         * @param result Json格式的请求结果
         * @param person_id 待删除的个体id
         * @return 0成功 -1失败
         */
        int DelPerson(rapidjson::Document &result, const std::string& person_id);

        /**
         * @brief AddFace
         * @param result Json格式的请求结果
         * @param person_id 新增人脸的个体身份id
         * @param imagePaths 待增加的包含人脸的图片本地路径，可加入多张（包体大小<2m）
         * @param data_type 图片数据类型 图片本地路径／url 0／1
         * @param tag 人脸备注信息，用户自解释字段
         * @return
         */
        int AddFace(rapidjson::Document &result, const std::string& person_id, const std::vector<std::string>& imagePaths, int data_type = 0, const std::string &tag="");

        /**
         * @brief DelFace
         * @param result Json格式的请求结果
         * @param person_id 待删除人脸的个体身份id
         * @param face_ids 待删除的人脸id
         * @return 0成功 -1失败
         */
        int DelFace(rapidjson::Document &result, const std::string& person_id, const std::vector<std::string>& face_ids);

        /**
         * @brief SetInfo
         * @param result Json格式的请求结果
         * @param person_id 待设置的个体身份id
         * @param person_name 新设置的个体名字
         * @param tag 新设置的人脸备注信息
         * @return 0成功 -1失败
         */
        int SetInfo(rapidjson::Document &result, const std::string& person_id, const std::string& person_name, const std::string& tag);

        /**
         * @brief GetInfo
         * @param result Json格式的请求结果
         * @param person_id 待查询的个体身份id
         * @return 0成功 -1失败
         */
        int GetInfo(rapidjson::Document &result, const std::string& person_id);

        /**
         * @brief GetGroupIds
         * @param result Json格式的请求结果
         * @return 0成功 -1失败
         */
        int GetGroupIds(rapidjson::Document &result);

        /**
         * @brief GetPersonIds
         * @param result Json格式的请求结果
         * @param group_id 待查询的组id
         * @return 0成功 -1失败
         */
        int GetPersonIds(rapidjson::Document &result, const std::string& group_id);

        /**
         * @brief GetFaceIds
         * @param result Json格式的请求结果
         * @param person_id 待查询的个体id
         * @return 0成功 -1失败
         */
        int GetFaceIds(rapidjson::Document &result, const std::string& person_id);

        /**
         * @brief GetFaceInfo
         * @param result Json格式的请求结果
         * @param face_id 待查询的人脸id
         * @return 0成功 -1失败
         */
        int GetFaceInfo(rapidjson::Document &result, const std::string &face_id);

        /**
         * @brief FuzzyDetect
         * @param result Json格式的请求结果
         * @param imagePath 图片本地路径／url
         * @param data_type 图片数据类型 本地路径／url 0／1
         * @param cookie
         * @return 0成功 -1失败
         */
        int FuzzyDetect(rapidjson::Document &result, const std::string &imagePath, int data_type = 0, const std::string &cookie = "");

        /**
         * @brief FoodDetect
         * @param result Json格式的请求结果
         * @param imagePath 图片本地路径／url
         * @param data_type 图片数据类型 本地路径／url 0／1
         * @param cookie
         * @return 0成功 -1失败
         */

        int FoodDetect(rapidjson::Document &result, const std::string &imagePath, int data_type = 0, const std::string &cookie = "");

        /**
         * @brief ImageTag 图片分类
         * @param result Json格式的请求结果
         * @param imagePath 图片本地路径／url
         * @param data_type 图片数据类型 本地路径／url 0／1
         * @param cookie
         * @return 0成功 -1失败
         */
        int ImageTag(rapidjson::Document &result, const std::string &imagePath, int data_type = 0, const std::string &cookie = "");

        /**
         * @brief ImagePorn 图片鉴黄
         * @param result Json格式的请求结果
         * @param imagePath 图片本地路径／url
         * @param data_type 图片数据类型 本地路径／url 0／1
         * @param cookie
         * @return 0成功 -1失败
         */
        int ImagePorn(rapidjson::Document &result, const std::string &imagePath, int data_type = 0, const std::string &cookie = "");

        /**
         * @brief ImageTerrorism 图片暴恐检测
         * @param result Json格式的请求结果
         * @param imagePath 图片本地路径／url
         * @param data_type 图片数据类型 本地路径／url 0／1
         * @param cookie
         * @return 0成功 -1失败
         */
        int ImageTerrorism(rapidjson::Document &result, const std::string &imagePath, int data_type = 0, const std::string &cookie = "");

        /**
         * @brief CarClassify 车辆属性识别
         * @param result Json格式的请求结果
         * @param imagePath 图片本地路径／url
         * @param data_type 图片数据类型 本地路径／url 0／1
         * @param cookie
         * @return 0成功 -1失败
         */
        int CarClassify(rapidjson::Document &result, const std::string &imagePath, int data_type = 0, const std::string &cookie = "");

        /**
         * @brief IdcardOcr 身份证OCR识别
         * @param result
         * @param imagePath
         * @param data_type 图片数据类型 本地路径／url 0／1
         * @param card_type 身份证图片类型，0-正面，1-反面
         * @return
         */
        int IdcardOcr(rapidjson::Document &result, const std::string &imagePath, int data_type = 0, int card_type = 0);

        /**
         * @brief LiveGetFour
         * @param result
         */
        int LiveGetFour(rapidjson::Document &result);

        /**
         * @brief LiveDetectFour
         * @param result
         * @param videoPath
         * @param validate_data
         * @param imagePath
         * @param compare_flag
         * @return
         */
        int LiveDetectFour(rapidjson::Document &result, const std::string &videoPath, const std::string &validate_data, const std::string &imagePath, bool compare_flag = 1);

        /**
         * @brief IdCardLiveDetectFour
         * @param result
         * @param videoPath
         * @param validate_data
         * @param id
         * @param name
         * @return
         */
        int IdCardLiveDetectFour(rapidjson::Document &result, const std::string &videoPath, const std::string &validate_data, const std::string &id, const std::string &name);

        /**
         * @brief IdCardFaceCompare
         * @param result
         * @param id
         * @param name
         * @param imagePath
         * @param data_type
         * @return
         */
        int IdCardFaceCompare(rapidjson::Document &result, const std::string &id, const std::string &name, const std::string &imagePath, int data_type = 0);

        /**
         * @brief IdCardFaceCompare
         * @param result
         * @param id
         * @param name
         * @return
         */
        int ValidateIdCard(rapidjson::Document &result, const std::string &id, const std::string &name);

        
        /**
         * @brief GeneralOcr 
         * @param result    Json格式的请求结果
         * @param imagePath 图片本地路径／url
         * @param data_type 图片数据类型 本地路径／url 0／1 
         * @return
         */
        int GeneralOcr(rapidjson::Document &result, const std::string &imagePath, int data_type=0);


        /**
         * @brief BcOcr 
         * @param result    Json格式的请求结果
         * @param imagePath 图片本地路径／url
         * @param data_type 图片数据类型 本地路径／url 0／1 
         * @return
         */
        int BcOcr(rapidjson::Document &result, const std::string &imagePath, int data_type=0);


        /**
         * @brief DriverLicenseOcr 
         * @param result    Json格式的请求结果
         * @param imagePath 图片本地路径／url
         * @param data_type 图片数据类型 本地路径／url 0／1 
         * @param card_type 图片类型:行驶证/驾驶证 0/1
         * @return
         */
        int DriverLicenseOcr(rapidjson::Document &result, const std::string &imagePath, int data_type=0, int card_type=0);

        /**
         * @brief CreditCardOcr
         * @param result    Json格式的请求结果
         * @param imagePath 图片本地路径／url
         * @param data_type 图片数据类型 本地路径／url 0／1
         * @return
         */
        int CreditCardOcr(rapidjson::Document &result, const std::string &imagePath, int data_type = 0);

        /**
         * @brief BizLicenseOcr
         * @param result    Json格式的请求结果
         * @param imagePath 图片本地路径／url
         * @param data_type 图片数据类型 本地路径／url 0／1
         * @return
         */
        int BizLicenseOcr(rapidjson::Document &result, const std::string &imagePath, int data_type = 0);

        /**
         * @brief PlateOcr
         * @param result    Json格式的请求结果
         * @param imagePath 图片本地路径／url
         * @param data_type 图片数据类型 本地路径／url 0／1
         * @return
         */
        int PlateOcr(rapidjson::Document &result, const std::string &imagePath, int data_type=0);


    private:
        int curl_method(const std::string& addr, const std::string &req_str, std::string &rsp_str);
        
    private:
        static std::string host_youtu;
        static std::string host_face_in_youtu;
        std::string host;
        AppSign app_sign;
        std::string app_id;
};

#endif
