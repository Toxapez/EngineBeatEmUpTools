#include "UIpm.h"

UIpm UIpm::instance;

UIpm::UIpm() {
	layer = 10;
	showingItemInfo = false;
	titleTimeline.events.push_back(Meth::SegToFrame(.04));
	titleTimeline.events.push_back(Meth::SegToFrame(1.5));
	titleTimeline.events.push_back(Meth::SegToFrame(.1));
	titleOffset = Vector2(SDLClass::screenSizeX * -.5, 0);
	titleTimeline.Deactive();
}

void UIpm::AfterStaticStart() {
	barra.Set("ui/uipm.png");
	killcount.Set("ui/killcount.png");
	itemBox.Set("ui/itembox.png");
	itemNameBox.Set("ui/itemNAMEbox.png");
	flecha.Set("ui/flecha.png");
	dinero.Set("ui/dineroicon.png");
	spawnermasuno.Set("ui/spawner_masuno.png");
	spawnermasuno.camDependent = false;
	killcount.camDependent = false;
	barra.camDependent = false;
	itemBox.camDependent = false;
	itemNameBox.camDependent = false;
	flecha.camDependent = false;
	dinero.camDependent = false;
}

void UIpm::Draw() {
	if (Player::player.exists) {
		Vector2 barraPos = Vector2((SDLClass::screenSizeX) * .1, (SDLClass::screenSizeY ) * .05);
		//furia
		FigureDrawer::DrawFillRect(Rect(barraPos + Vector2(-50, -35) * SDLClass::screenWidthStreching, Vector2(190 , 16) * SDLClass::screenWidthStreching), Color(), false);
		FigureDrawer::DrawFillRect(Rect(barraPos + Vector2(-50, -35) * SDLClass::screenWidthStreching, Vector2(190 * (PlayerVariables::instance.liquid / 200), 16) * SDLClass::screenWidthStreching), Color(0, 0, 0), false);
		// vida
		FigureDrawer::DrawFillRect(Rect(barraPos + Vector2(-50, -20) * SDLClass::screenWidthStreching, Vector2(200 , 28) * SDLClass::screenWidthStreching), Color(), false);
		FigureDrawer::DrawFillRect(Rect(barraPos + Vector2(-50, -20) * SDLClass::screenWidthStreching, Vector2(200 * (Player::player.health / Player::player.maxHealth.Get()), 28) * SDLClass::screenWidthStreching), Color(200, 0, 0), false);
		
		barra.Draw(barraPos);
		

		if (LevelState::instance.nEnemies > 0) {
			Vector2 kcPos = Vector2(SDLClass::screenSizeX * .16, SDLClass::screenSizeY * 0);
			killcount.Draw(barraPos + kcPos);


			


			Text kcText = Text(std::to_string(LevelState::instance.nEnemies) + (LevelState::instance.maxEnemies != 0 ? "/" + std::to_string(LevelState::instance.maxEnemies) : ""),
				58, Color(0), "altehaas", false);
			TextDrawer::DrawSimpleText(kcText, barraPos + kcPos + Vector2(SDLClass::screenSizeX * .07, 0));

			if (preEnemies == LevelState::instance.nEnemies - 1)
				spawnermasunoCounter = 1;


			if (spawnermasunoCounter > 0) {
				Vector2 offsetSpanwermas1 = Vector2(0, SDLClass::screenSizeY * -.1 * (1 - (spawnermasunoCounter / 1)));
				spawnermasuno.Draw(barraPos + kcPos + Vector2(SDLClass::screenSizeX * .07, 0) + Vector2(SDLClass::screenSizeX * .018, SDLClass::screenSizeY * -.008) + offsetSpanwermas1);

				spawnermasunoCounter -= Kang::gameTimeSpeed * .01;
			}
		}

		Vector2 moneyPos = Vector2(SDLClass::screenSizeX * .48, SDLClass::screenSizeY * 0);
		dinero.Draw(barraPos + moneyPos);
		Text moneyText = Text(std::to_string(PlayerVariables::instance.money),
			58, Color(0), "altehaas", false);
		TextDrawer::DrawSimpleText(moneyText, barraPos + moneyPos + Vector2(SDLClass::screenSizeX * .03, 0));


		Vector2 itemBoxPos = Vector2(SDLClass::screenSizeX  * .5, SDLClass::screenSizeY * .075);
		itemBox.Draw(itemBoxPos,true,0,SDL_Rect(),1.7);
		auto&& hO = PlayerVariables::instance.handObject;
		if (hO.name != "") {
			if (hO.sprite)
				SDLClass::DrawTexture(hO.sprite, itemBoxPos);
			else
				hO.ss->Draw(hO.nS,itemBoxPos,false,true,0,SDL_Rect(),1.7);
		}
		if (hO.showRecolectableInfo) {
			titleTimeline.Reset();
			hO.showRecolectableInfo = false;
			titleObject = hO;
		}

		if (titleTimeline.isActive()) {
			auto&& hO = titleObject;
			Vector2 descOffset;
			if (titleTimeline.events[0].active) {
				titleOffset = Vector2(SDLClass::screenSizeX * (-1 * (1-titleTimeline.Percentage())), 0);
			}
			else if (titleTimeline.events[1].active) {
				titleOffset = Vector2();
			}
			else if (titleTimeline.events[2].active) {
				titleOffset = Vector2(SDLClass::screenSizeX * (1 * titleTimeline.Percentage()), 0);
			}
			titleTimeline.Run();

			Vector2 titleItemPos = Vector2(SDLClass::screenSizeX * .5, SDLClass::screenSizeY * .2) + titleOffset;
			itemNameBox.Draw(titleItemPos);

			Text titleText = Text();
			Text descText = Text();
			titleText = Text(hO.title, 60, Color(), "altehaas", false);
			descText = Text(hO.description, 45, Color(), "altehaas", false);
			
			
			if (titleTimeline.events[1].active) {
				if(titleTimeline.Percentage() < .1)
					descOffset = Vector2(0,SDLClass::screenSizeY * (.065 * (titleTimeline.Percentage()/.1)));
				else descOffset = Vector2(0, SDLClass::screenSizeY * .065 );
				TextDrawer::DrawSimpleText(descText, titleItemPos + descOffset);
			}
			TextDrawer::DrawSimpleText(titleText, titleItemPos);
		}
		if (Player::player.poitingArrowDir) {
			Vector2 dir = (*Player::player.poitingArrowDir - Cam::currentCam->transform.position);
			Vector2 pos = SDLClass::GetScreenSizeVector2() / 2 + dir;
			pos.x = Meth::Clamp(pos.x, SDLClass::screenSizeX * .025, SDLClass::screenSizeX * .975);
			pos.y = Meth::Clamp(pos.y, SDLClass::screenSizeY * .05, SDLClass::screenSizeY * .95);
			flecha.Draw(pos,true,dir.GetAngle());
		}
	}
	preEnemies = LevelState::instance.nEnemies;
}