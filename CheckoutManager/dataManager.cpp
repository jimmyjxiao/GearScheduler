#pragma once
#include "pch.h"
#include "dataManager.h"
#include <sstream>
namespace dataspace
{
	int32 dataManager::GetNewColor()
	{
		const uint8 A = 255;
		uint8 R, G, B;
		R = rand() % 255;
		G = rand() % 255;
		B = rand() % 255;
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
		__debugbreak();
		return color;
	}
	Windows::UI::Color dataManager::inttocolor(int32 number)
	{
		return Windows::UI::ColorHelper::FromArgb((number >> 24 & 255), (number >> 16 & 255), (number >> 8 & 255), (number & 255));
	}
	dataManager::dataManager()
	{
		auto path = Windows::Storage::ApplicationData::Current->LocalFolder->Path + L"\\inventory.db";

		try
		{
			inventory = new sqlite::database((const char16_t*)path->Data());
			*inventory << "CREATE TABLE IF NOT EXISTS 'checkouts' (`checkoutID` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, `teamID` tinyint, `checkedout` bit, `chktime` INTEGER NOT NULL, `typeID` tinyint, `duetime` INTEGER NOT NULL, `actchktime` INTEGER, `actreturntime` INTEGER, `returned` INTEGER); CREATE TABLE IF NOT EXISTS 'Teams' (`teamID` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, `TeamName` TEXT NOT NULL, `password` BLOB NOT NULL, `color` BLOB UNIQUE); CREATE TABLE IF NOT EXISTS 'deviceType' (`deviceName` text NOT NULL, `typeID` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, `color` INTEGER); CREATE TABLE IF NOT EXISTS 'devices' (`deviceID` INTEGER NOT NULL, `typeID` tinyint NOT NULL, `available` bit, `Currentholder` TEXT, `desc` TEXT, `PublicID` TEXT, `ForcedCheckout` INTEGER, PRIMARY KEY(`deviceID`)); ";
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
				"WHERE (? BETWEEN checkouts.chktime AND checkouts.duetime) OR (? BETWEEN checkouts.chktime AND checkouts.duetime) OR (checkouts.chktime BETWEEN ? AND ?) AND (deviceType.deviceName = ?);");

		}
		catch (sqlite::sqlite_exception z)
		{
			auto x = z.what();

			__debugbreak();
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
			__debugbreak();
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

			__debugbreak();
		}

	}

	bool dataManager::scheduleCheckout(CheckoutInfo adding)
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
			__debugbreak();
		}
		return false;
	}

	bool dataManager::fullfillCheckout(const CheckoutInfo & checkout, std::u16string hash, std::u16string deviceID)
	{
		if (!passwordCheck(checkout.Team, hash))
			throw 'P';
		try
		{
			*inventory <<
				u"UPDATE checkouts "
				"SET checkedout=1, actchktime=(SELECT strftime('%s','now')),  returned=0 "
				"WHERE checkoutID = ? "
				<< checkout.checkoutID;
			*inventory <<
				u"UPDATE devices "
				"SET available=0, CurrentHolder = ? "
				"WHERE publicID = ?"
				<< checkout.Team
				<< deviceID;
		}
		catch (std::exception e)
		{
			__debugbreak();
		}
		return true;
	}

	void dataManager::forceCheckout(std::u16string deviceID, std::u16string team)
	{
		*inventory <<
			"UPDATE devices "
			"SET available=0, CurrentHolder=? "
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
		*inventory <<
			u"SELECT typeID FROM devices WHERE PublicID = ?"
			<< deviceID
			>> [&](int z)
		{
			deviceFound = true;
			time_t currentTime;
			time(&currentTime);
			auto x = getCheckouts(currentTime, currentTime + 60, z);
			auto it = std::find_if(x.begin(), x.end(), [team, hash, deviceID, this](CheckoutInfo v)
			{
				return (team == v.Team);
			});
			if (it == x.end())
			{
				auto numpair = getnumofdevices(z);
				throw (std::make_tuple(numpair.first, numpair.second, x));
			}
			else
			{
				fullfillCheckout(*it, hash, deviceID);
				returning = *it;
			}
		};
		if (!deviceFound)
		{
			throw 'N';
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
				//				__debugbreak();
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
			__debugbreak();
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
				"WHERE (? BETWEEN checkouts.chktime AND checkouts.duetime) OR (? BETWEEN checkouts.chktime AND checkouts.duetime) OR (checkouts.chktime BETWEEN ? AND ?) AND (deviceType.typeID = ?);"
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
			__debugbreak();
		}
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
			__debugbreak();
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
				__debugbreak();

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
			catch (sqlite::exceptions::constraint)
			{
				//most likely we've generated a non-unique color. Just ignore and generate again until it works.
				__debugbreak();
			}
		}

	}

	void dataManager::addDevice(std::u16string desc, std::u16string type)
	{
		*inventory <<
			u"INSERT INTO devices (typeID, desc, PublicID, available) "
			"VALUES ((SELECT typeID FROM deviceType WHERE deviceName = ?), ?, (SELECT abs(random()) % 999), 1)"
			<< type
			<< desc;
	}

	bool dataManager::deleteTeam(std::u16string name)
	{
		*inventory <<
			"DELETE FROM Teams"
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
			__debugbreak();
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
			__debugbreak();
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