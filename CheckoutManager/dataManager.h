#pragma once

#include "sqlite_modern_cpp\hdr\sqlite_modern_cpp.h"
#define ViewByTeam 1
#define ViewByDevice 0

namespace dataspace
{
	class dataManager
	{
	private:
		std::function<Windows::UI::Color(bool)> getnewcolor;
		static int32 GetNewColor();

		static int dummycallback(void *NotUsed, int argc, char **argv, char **azColName) { OutputDebugString(L"dummy callback called"); return 0; };
		std::unique_ptr<sqlite::database_binder>  getcheckoutprepnd;
		sqlite::database * inventory;


		std::unique_ptr<sqlite::database_binder> getcheckoutprepyd;
	public:
		static int32 colortoint(Windows::UI::Color z);
		static Windows::UI::Color inttocolor(int32 number);
		dataManager();
		dataManager(std::function<Windows::UI::Color(bool)> colorFunc);
		struct CheckoutInfo
		{
			static bool isSameNotfulfilled(const CheckoutInfo& left, const CheckoutInfo& right)
			{
				return ((left.checkoutTime == right.checkoutTime) && (left.duedate == right.duedate) && (left.checkoutID == right.checkoutID) && (left.Team == right.Team) && (left.deviceType == right.deviceType));
			}
			std::u16string Team;
			std::u16string deviceType;
			time_t checkoutTime;
			time_t duedate;
			time_t actualchktime;
			time_t actualreturntime;
			int checkoutID = NULL;
			bool fullfilled = false;

		};
		void returndevice(int ID);
		bool scheduleCheckout(CheckoutInfo& adding);
		void editCheckout(const CheckoutInfo& adding);
		bool fullfillCheckout(const CheckoutInfo & checkout, std::u16string hash, std::u16string deviceID);
		void forceCheckout(std::u16string deviceID, std::u16string team);
		CheckoutInfo fullfillCheckout(std::u16string team, std::u16string hash, std::u16string deviceID);
		std::vector<CheckoutInfo> getCheckouts(time_t startdate, time_t enddate);
		std::vector<CheckoutInfo> getCheckouts(time_t startdate, time_t enddate, std::u16string deviceType);
		std::vector<std::pair<CheckoutInfo, int>> getOverdueCheckouts();
		std::vector<dataManager::CheckoutInfo> getCheckouts(time_t startdate, time_t enddate, int deviceType);
		bool passwordCheck(std::u16string team, std::u16string hash);
		bool addTeam(std::u16string name, std::u16string hash, Windows::UI::Color z);
		int addTeam(std::u16string name, std::u16string hash);
		bool addDevicetype(std::u16string name, Windows::UI::Color color);
		int addDevicetype(std::u16string name);
		void addDevice(std::u16string desc, std::u16string type);
		bool deleteTeam(std::u16string name);
		void deleteDeviceType(std::u16string name);
		void deleteDevice(int ID);
		bool deleteTeam(int TeamID);
		char getnumofdevices(std::u16string type);
		std::pair<char, std::u16string> getnumofdevices(int type);
		std::unordered_map<std::u16string, Windows::UI::Color> getTeams();
		std::map<std::u16string, Windows::UI::Color> getTeamsmap();
		std::unordered_map<std::u16string, Windows::UI::Color>  getdeviceTypes();
		std::map<std::u16string, Windows::UI::Color>  getdeviceTypesmap();
		std::u16string getdevicetypefromPubID(int id);
		void deleteCheckout(int id);
		std::unordered_multimap< std::u16string, std::tuple<bool, std::u16string, std::u16string, int>> getDevices(); // Key: DeviceType, Values: Available, currentholder, description, deviceID
		~dataManager();

	};

}