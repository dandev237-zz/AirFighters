#pragma once

//Node categories, used by the command class
namespace Category
{
	//Bitwise OR operator allows us to combine different categories
	//Handy in case you want to send a command to multiple nodes
	enum class Type
	{
		None = 0,
		Scene = 1 << 0,
		PlayerAircraft = 1 << 1,
		AlliedAircraft = 1 << 2,
		EnemyAircraft = 1 << 3,
	};
}