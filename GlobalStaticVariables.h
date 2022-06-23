#pragma once
struct GlobalStaticVariables
{
	static bool hasEnemyRandomTalk;
	static void FirstUpdate() {
		hasEnemyRandomTalk = false;
	}
};

