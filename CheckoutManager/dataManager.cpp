#pragma once
#include "pch.h"
#include "dataManager.h"
#include <sstream>
#include <random>
namespace dataspace
{
	std::mt19937 dataManager::ran;
	int32 dataManager::GetNewColor()
	{
		static std::uniform_int_distribution<int> uchannel(0, 255);
		const uint8 A = 255;
		uint8 R, G, B;
		R = uchannel(ran);
		G = uchannel(ran);
		B = uchannel(ran);
		uint32_t color = 0;
		color |= A << 24;
		color |= R << 16;
		color |= G << 8;
		color |= B;
		return color;
	}
	int32 dataManager::colortoint(Windows::UI::Color z)
	{
		int32 color = 0;
		color |= z.A << 24;
		color |= z.R << 16;
		color |= z.G << 8;
		color |= z.B;
		////__debugbreak();
		return color;
	}
	Windows::UI::Color dataManager::inttocolor(int32 number)
	{
		return Windows::UI::ColorHelper::FromArgb((number >> 24 & 255), (number >> 16 & 255), (number >> 8 & 255), (number & 255));
	}
	dataManager::dataManager()
	{
		auto path = Windows::Storage::ApplicationData::Current->LocalFolder->Path + L"\\inventory.db";
		std::random_device rd;
		ran = std::mt19937(rd());
		try
		{
			inventory = new sqlite::database((const char16_t*)path->Data());

			*inventory << "CREATE TABLE IF NOT EXISTS 'checkouts' ( `checkoutID` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, `teamID` tinyint, `checkedout` bit, `chktime` INTEGER NOT NULL, `typeID` tinyint, `duetime` INTEGER NOT NULL, `actchktime` INTEGER, `actreturntime` INTEGER, `returned` INTEGER, `devicepubID` INTEGER ); ";
			*inventory <<
				"CREATE TABLE IF NOT EXISTS 'Teams' (`teamID` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, `TeamName` TEXT NOT NULL UNIQUE, `password` BLOB NOT NULL, `color` BLOB UNIQUE)";
			*inventory <<
				"CREATE TABLE IF NOT EXISTS 'deviceType' ( `deviceName` text NOT NULL UNIQUE, `typeID` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, `color` INTEGER )";
				*inventory <<
				"CREATE TABLE IF NOT EXISTS 'devices' ( `deviceID` INTEGER NOT NULL, `typeID` tinyint NOT NULL, `available` bit, `Currentholder` TEXT, `desc` TEXT, `PublicID` TEXT UNIQUE, `ForcedCheckout` INTEGER, `checkoutID` INTEGER, PRIMARY KEY(`deviceID`) )";
			getcheckoutprepnd = std::make_unique<sqlite::database_binder>(*inventory << u"SELECT Teams.TeamName, checkouts.chktime, deviceType.deviceName, checkouts.duetime, checkouts.actchktime, checkouts.actreturntime, checkouts.checkoutID, checkouts.checkedout "
				"FROM checkouts "
				"INNER JOIN Teams "
				"ON checkouts.teamID=Teams.teamID "
				"INNER JOIN deviceType "
				"ON checkouts.typeID=devicetype.typeID "
				"WHERE (? BETWEEN checkouts.chktime AND checkouts.duetime) OR (? BETWEEN checkouts.chktime AND checkouts.duetime) OR (checkouts.chktime BETWEEN ? AND ?);");

			getcheckoutprepyd = std::make_unique<sqlite::database_binder>(*inventory << u"SELECT Teams.TeamName, checkouts.chktime, deviceType.deviceName, checkouts.duetime, checkouts.actchktime, checkouts.actreturntime, checkouts.checkoutID, checkouts.checkedout "
				"FROM checkouts "
				"INNER JOIN Teams "
				"ON checkouts.teamID=Teams.teamID "
				"INNER JOIN deviceType "
				"ON checkouts.typeID=devicetype.typeID "
				"WHERE ((? BETWEEN checkouts.chktime AND checkouts.duetime) OR (? BETWEEN checkouts.chktime AND checkouts.duetime) OR (checkouts.chktime BETWEEN ? AND ?)) AND (deviceType.typeID = ?);");

		}
		catch (sqlite::sqlite_exception z)
		{
			
			auto x = z.what();

			////__debugbreak();
		}


	}

	dataManager::dataManager(std::function<Windows::UI::Color(bool)> colorFunc)
	{
		getnewcolor = colorFunc;
		auto path = Windows::Storage::ApplicationData::Current->LocalFolder->Path + L"\\inventory.db";
		try
		{
			inventory = new sqlite::database((const char16_t*)path->Data());
			getcheckoutprepnd = std::make_unique<sqlite::database_binder>(*inventory << u"SELECT Teams.TeamName, checkouts.chktime, deviceType.deviceName, checkouts.duetime, checkouts.actchktime, checkouts.actreturntime "
				"FROM checkouts "
				"INNER JOIN Teams "
				"ON checkouts.teamID=Teams.teamID "
				"INNER JOIN deviceType "
				"ON checkouts.typeID=devicetype.typeID "
				"WHERE (? BETWEEN checkouts.chktime AND checkouts.duetime) OR (? BETWEEN checkouts.chktime AND checkouts.duetime) OR (checkouts.chktime BETWEEN ? AND ?);");
			////__debugbreak();
			/*
			getcheckoutprepyd = &(*inventory << u"SELECT Teams.TeamName, checkouts.chktime, deviceType.deviceName, checkouts.duetime, checkouts.actchktime, checkouts.actreturntime "
			"FROM checkouts "
			"INNER JOIN Teams "
			"ON checkouts.teamID=Teams.teamID "
			"INNER JOIN deviceType "
			"ON checkouts.typeID=devicetype.typeID; "
			"WHERE (? BETWEEN checkouts.chktime AND checkouts.duetime) OR (? BETWEEN checkouts.chktime AND checkouts.duetime) OR (checkouts.chktime BETWEEN ? AND ?) AND (deviceType.deviceName=?)");
			*/
		}
		catch (sqlite::sqlite_exception z)
		{
			auto x = z.what();

			////__debugbreak();
		}

	}

	void dataManager::returndevice(int ID)
	{
		int checkoutID = 0;
		try
		{
			try
			{
				*inventory
					<< u"SELECT checkoutID FROM devices "
					"WHERE PublicID = ?"
					<< ID
					>> checkoutID;
				*inventory
					<< u"UPDATE checkouts "
					"SET returned=1, actreturntime=(SELECT strftime('%s','now')) "
					"WHERE checkoutID = ?;"
					<< checkoutID;
			}
			catch (std::exception e)
			{
				////__debugbreak();
			}
			*inventory
				<< u"UPDATE devices "
				"SET available=1, currentholder=NULL, checkoutID=NULL "
				"WHERE PublicID = ?"
				<< ID;
		}
		catch (std::exception e)
		{

		}
	}

	bool dataManager::scheduleCheckout(CheckoutInfo & adding)
	{
		try
		{
			*inventory <<
				u"INSERT INTO checkouts (teamID, checkedout, chktime, typeID, duetime) "
				"VALUES ((SELECT teamID FROM Teams WHERE TeamName = ?), ?, ?, (SELECT typeID from deviceType WHERE deviceName = ?), ?);"
				<< adding.Team
				<< 0
				<< adding.checkoutTime
				<< adding.deviceType
				<< adding.duedate;
		}
		catch (std::exception e)
		{
			////__debugbreak();
		}
		return false;
	}

	void dataManager::editCheckout(const CheckoutInfo & adding)
	{
		try
		{
			*inventory <<
				u"UPDATE checkouts "
				"SET teamID = (SELECT teamID FROM Teams WHERE TeamName = ?), checkedout = ?, chktime = ?, typeID = (SELECT typeID from deviceType WHERE deviceName = ?), duetime = ?  "
				"WHERE checkoutID = ?;"
				<< adding.Team
				<< (int)adding.fullfilled
				<< adding.checkoutTime
				<< adding.deviceType
				<< adding.duedate
				<< adding.checkoutID;
		}
		catch (std::exception e)
		{
			////__debugbreak();
		}
	}

	bool dataManager::fullfillCheckout(const CheckoutInfo & checkout, std::u16string hash, std::u16string deviceID)
	{
		if (!passwordCheck(checkout.Team, hash))
			throw 'P';
		try
		{
			*inventory <<
				u"UPDATE checkouts "
				"SET checkedout=1, actchktime=(SELECT strftime('%s','now')),  returned=0, devicepubID = ? "
				"WHERE checkoutID = ? "
				<< deviceID
				<< checkout.checkoutID;
			*inventory <<
				u"UPDATE devices "
				"SET available=0, CurrentHolder = ?, checkoutID = ?"
				"WHERE PublicID = ?"
				<< checkout.Team
				<< checkout.checkoutID
				<< deviceID;
		}
		catch (std::exception e)
		{
			////__debugbreak();
		}
		return true;
	}

	void dataManager::forceCheckout(std::u16string deviceID, std::u16string team)
	{
		*inventory <<
			"UPDATE devices "
			"SET available=0, CurrentHolder=?, ForcedCheckout=1 "
			"WHERE publicID=?"
			<< team
			<< deviceID;
	}

	dataManager::CheckoutInfo dataManager::fullfillCheckout(std::u16string team, std::u16string hash, std::u16string deviceID)
	{
		if (!passwordCheck(team, hash))
			throw 'P';
		bool deviceFound = false;
		CheckoutInfo returning;
		try
		{
			*inventory <<
				u"SELECT typeID FROM devices WHERE PublicID = ? "
				<< deviceID
				>> [&](int z)
			{
				deviceFound = true;
				time_t currentTime;
				time(&currentTime);
				auto x = getCheckouts(currentTime, currentTime + 60, z);
				if (x.size() > 0)
				{
					auto it = std::find_if(x.begin(), x.end(), [team, hash, deviceID, this](CheckoutInfo v)
					{
						return ((team == v.Team) && !v.fullfilled);
					});
					if (it == x.end())
					{
						auto numpair = getnumofdevices(z);
						throw (std::make_tuple(numpair.first, numpair.second, x));
					}
					else
					{
						returndevice(std::stoi((const wchar_t*)deviceID.data()));
						fullfillCheckout(*it, hash, deviceID);
						returning = *it;
					}
				}
				else
					throw'U';
			};
			if (!deviceFound)
			{
				throw 'N';
			}
		}
		catch (std::exception e)
		{
			////__debugbreak();
		}
		return returning;
	}

	std::vector<dataManager::CheckoutInfo> dataManager::getCheckouts(time_t startdate, time_t enddate)
	{
		try {

			std::vector<dataManager::CheckoutInfo> returning = std::vector<dataManager::CheckoutInfo>();

			*getcheckoutprepnd
				<< startdate
				<< enddate
				<< startdate
				<< enddate
				>> [&](std::u16string TeamName, time_t date, std::u16string device, time_t due, time_t chkd, time_t retur, int checkoutID, int fullfilled)

			{
				//				//__debugbreak();
				CheckoutInfo adding =
				{
					TeamName,
					device,
					date,
					due



				};
				adding.checkoutID = checkoutID;
				adding.actualchktime = chkd;
				adding.actualreturntime = retur;
				adding.fullfilled = fullfilled;
				returning.push_back(adding);
			};

			return returning;
		}
		catch (std::exception e)
		{
			////__debugbreak();
		}
		getcheckoutprepnd->reset();

	}

	std::vector<dataManager::CheckoutInfo> dataManager::getCheckouts(time_t startdate, time_t enddate, std::u16string deviceType)
	{
		std::vector<dataManager::CheckoutInfo> returning = std::vector<dataManager::CheckoutInfo>();
		try
		{
			*inventory << u"SELECT Teams.TeamName, checkouts.chktime, deviceType.deviceName, checkouts.duetime, checkouts.actchktime, checkouts.actreturntime, checkouts.checkoutID "
				"FROM checkouts "
				"INNER JOIN Teams "
				"ON checkouts.teamID=Teams.teamID "
				"INNER JOIN deviceType "
				"ON checkouts.typeID=devicetype.typeID "
				"WHERE ((? BETWEEN checkouts.chktime AND checkouts.duetime) OR (? BETWEEN checkouts.chktime AND checkouts.duetime) OR (checkouts.chktime BETWEEN ? AND ?)) AND (deviceType.deviceName = ?);"
				<< startdate
				<< enddate
				<< startdate
				<< enddate
				<< deviceType
				>> [&](std::u16string TeamName, time_t date, std::u16string device, time_t due, std::unique_ptr<time_t> chkd, std::unique_ptr<time_t> retur, int checkoutID)

			{

				CheckoutInfo adding =
				{
					TeamName,
					device,
					date,
					due



				};
				adding.checkoutID = checkoutID;
				if (chkd != nullptr)
				{
					adding.actualchktime = *chkd;
					if (retur != nullptr)
					{
						adding.actualreturntime = *retur;
					}
				}
				else
					adding.actualchktime = NULL, adding.actualreturntime = NULL;
				returning.push_back(adding);
			};

			return returning;
		}
		catch (std::exception e)
		{
			////__debugbreak();
		}
	}
	std::vector<std::pair<dataManager::CheckoutInfo, int>> dataManager::getOverdueCheckouts()
	{
		std::vector<std::pair<CheckoutInfo, int>> returning = std::vector<std::pair<CheckoutInfo, int>>();
		*inventory << u"SELECT Teams.TeamName, checkouts.chktime, deviceType.deviceName, checkouts.duetime, checkouts.actchktime, checkouts.actreturntime, checkouts.checkoutID, checkouts.checkedout, checkouts.devicepubID "
			"FROM checkouts "
			"INNER JOIN Teams "
			"ON checkouts.teamID=Teams.teamID "
			"INNER JOIN deviceType "
			"ON checkouts.typeID=devicetype.typeID "
			"WHERE checkouts.checkedout = 1 AND checkouts.returned = 0 AND (SELECT strftime('%s','now')) > checkouts.duetime;"
			>>
			[&](std::u16string TeamName, time_t date, std::u16string device, time_t due, time_t chkd, time_t retur, int checkoutID, int fullfilled, int deviceID)

		{
			//				//__debugbreak();
			CheckoutInfo adding =
			{
				TeamName,
				device,
				date,
				due



			};
			adding.checkoutID = checkoutID;
			adding.actualchktime = chkd;
			adding.actualreturntime = retur;
			adding.fullfilled = fullfilled;
			returning.emplace_back(adding, deviceID);
		};
		return returning;
	}

	bool dataManager::passwordCheck(std::u16string team, std::u16string hash)
	{
		bool returning;
		*inventory <<
			"SELECT password FROM Teams WHERE TeamName = ?"
			<< team
			>> [&](std::u16string password)
		{
			if (password == hash)
				returning = true;
			else
				returning = false;
		};
		return returning;
	}


	std::vector<dataManager::CheckoutInfo> dataManager::getCheckouts(time_t startdate, time_t enddate, int deviceType)
	{
		std::vector<dataManager::CheckoutInfo> returning = std::vector<dataManager::CheckoutInfo>();
		try
		{
			*getcheckoutprepyd
				<< startdate
				<< enddate
				<< startdate
				<< enddate
				<< deviceType
				>> [&](std::u16string TeamName, time_t date, std::u16string device, time_t due, time_t chkd, time_t retur, int checkoutID, int fullfilled)

			{

				CheckoutInfo adding =
				{
					TeamName,
					device,
					date,
					due



				};
				adding.checkoutID = checkoutID;
				adding.actualchktime = chkd;
				adding.actualreturntime = retur;
				adding.fullfilled = fullfilled;
				returning.push_back(adding);
			};

			return returning;
		}
		catch (std::exception e)
		{
			////__debugbreak();
		}
	}

	


	bool dataManager::addTeam(std::u16string name, std::u16string hash, Windows::UI::Color z)
	{
	



		*inventory <<
			"INSERT INTO Teams VALUES (?,?,?);"
			<< name
			<< hash
			<< colortoint(z);
		return false;

	}

	int dataManager::addTeam(std::u16string name, std::u16string hash)
	{
		while (1)
		{
			

			try
			{
				auto newcolor = GetNewColor();
				*inventory <<
					"INSERT INTO Teams (TeamName, password, color) VALUES (?,?,?);"
					<< name
					<< hash
					<< newcolor;
				return newcolor;
			}
			catch (std::exception e)
			{
				int y = 0;
				*inventory << "SELECT count(*) FROM Teams WHERE TeamName = ?;"
					<< name
					>> y;
				if (y > 0)
					throw e;
				//__debugbreak();

			}
			
		}
	}

	bool dataManager::addDevicetype(std::u16string name, Windows::UI::Color color)
	{

		*inventory <<
			u"INSERT INTO deviceType (deviceName, color) "
			"VALUES (?, ?);"
			<< name
			<< colortoint(color);
		return false;
	}
	int dataManager::addDevicetype(std::u16string name)
	{
		while (1)
		{
			try
			{
				auto newcolor = GetNewColor();
				*inventory <<
					u"INSERT INTO deviceType (deviceName, color) "
					"VALUES (?, ?);"
					<< name
					<< newcolor;
				return newcolor;
			}
			catch (sqlite::exceptions::constraint z)
			{
				//most likely we've generated a non-unique color. Just ignore and generate again until it works. But maybe we have a non-unique device type name. check for that
				int y = 0;
				*inventory << "SELECT count(*) FROM deviceType WHERE deviceName = ?;"
					<< name
					>> y;
				if (y > 0)
					throw z;
				////__debugbreak();
			}
		}

	}

	int dataManager::addDevice(std::u16string desc, std::u16string type)
	{
		static std::uniform_int_distribution<int> pubIDgen(0, 999);
		while (1)
		{
			try
			{
			int ID = pubIDgen(ran);
			*inventory <<
				u"INSERT INTO devices (typeID, desc, PublicID, available) "
				"VALUES ((SELECT typeID FROM deviceType WHERE deviceName = ?), ?, ?, 1)"
				<< type
				<< desc
				<< ID;
			return ID;
			}
			catch (...) {};
		}
	}

	bool dataManager::deleteTeam(std::u16string name)
	{
		*inventory <<
			"DELETE FROM Teams "
			"WHERE TeamName = ?;"
			<< name;
		return false;
	}

	void dataManager::deleteDeviceType(std::u16string name)
	{
		*inventory <<
			"DELETE FROM deviceType "
			"WHERE deviceName = ?;"
			<< name;
	}

	void dataManager::deleteDevice(int ID)
	{
		try
		{
			*inventory <<
				"DELETE FROM devices "
				"WHERE PublicID = ?;"
				<< ID;
		}
		catch (std::exception e)
		{

		}
	}

	bool dataManager::deleteTeam(int TeamID)
	{
		*inventory <<
			"DELETE FROM Teams"
			"WHERE teamID = ?;"
			<< TeamID;
		return false;
	}

	char dataManager::getnumofdevices(std::u16string type)
	{
		int count = 0;
		try
		{
			*inventory << u"SELECT count(*) FROM devices "
				"INNER JOIN deviceType "
				"ON devices.typeID=deviceType.typeID "
				"WHERE deviceType.deviceName = ?"
				<< type
				>> count;
		}
		catch (std::exception e)
		{
			////__debugbreak();
		}
		return count;
	}
	std::pair<char, std::u16string> dataManager::getnumofdevices(int type)
	{
		int count = 0;
		std::u16string deviceName;
		try
		{
			*inventory << u"SELECT COUNT(devices.deviceID), deviceType.deviceName AS numdevices FROM devices "
				"inner join deviceType "
				"on devices.typeID = deviceType.typeID "
				"WHERE devices.typeID = ? "
				<< type
				>> tie(count, deviceName);
				
		}
		catch (std::exception e)
		{
			////__debugbreak();
		}
		return std::make_pair(count, deviceName);
	}

	std::unordered_map<std::u16string, Windows::UI::Color> dataManager::getTeams()
	{
		std::unordered_map<std::u16string, Windows::UI::Color> teams = std::unordered_map<std::u16string, Windows::UI::Color>();
		*inventory << u"select TeamName, color from teams;"
			>> [&](std::u16string name, int color)
		{
			teams.insert(std::make_pair(name, inttocolor(color)));
		};
		return teams;
	}

	std::map<std::u16string, Windows::UI::Color> dataManager::getTeamsmap()
	{
		std::map<std::u16string, Windows::UI::Color> teams = std::map<std::u16string, Windows::UI::Color>();
		*inventory << u"select TeamName, color from teams;"
			>> [&](std::u16string name, int color)
		{
			teams.insert(std::make_pair(name, inttocolor(color)));
		};
		return teams;
	}

	std::unordered_map<std::u16string, Windows::UI::Color>  dataManager::getdeviceTypes()
	{
		std::unordered_map<std::u16string, Windows::UI::Color> devices = std::unordered_map<std::u16string, Windows::UI::Color>();
		(*inventory) << u"select deviceName , color from deviceType;"
			>> [&](std::u16string dev, int color)
		{

			devices.insert(std::make_pair(dev, inttocolor(color)));

		};
		return devices;
	}

	std::map<std::u16string, Windows::UI::Color> dataManager::getdeviceTypesmap()
	{
		std::map<std::u16string, Windows::UI::Color> devices = std::map<std::u16string, Windows::UI::Color>();
		(*inventory) << u"select deviceName , color from deviceType;"
			>> [&](std::u16string dev, int color)
		{

			devices.insert(std::make_pair(dev, inttocolor(color)));

		};
		return devices;
	}

	std::u16string dataManager::getdevicetypefromPubID(int id)
	{
		std::u16string devtype;
		*inventory << u"SELECT deviceName FROM deviceType WHERE typeID=(SELECT typeID FROM devices WHERE PublicID =?);"
			<< id
			>> devtype;
		return devtype;
	}

	void dataManager::deleteCheckout(int id)
	{
		*inventory << u"DELETE FROM checkouts "
			"WHERE checkoutID = ?" << id;
	}

	std::unordered_multimap<std::u16string, std::tuple<bool, std::u16string, std::u16string, int>> dataManager::getDevices()
	{
		std::unordered_multimap<std::u16string, std::tuple<bool, std::u16string, std::u16string, int>> z;
		*inventory << u"SELECT deviceType.deviceName, devices.available, devices.Currentholder, devices.desc, devices.PublicID "
			"FROM devices "
			"INNER JOIN deviceType "
			"ON devices.typeID=deviceType.typeID" >> [&](std::u16string type, int available, std::u16string current, std::u16string desc, int ID)
		{
			z.insert(std::make_pair(type, std::make_tuple((bool)available, current, desc, ID)));
		};

		return z;
	}




	dataManager::~dataManager()
	{


		delete inventory;
	}
}