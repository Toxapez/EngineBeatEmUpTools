#include "BooleanQuestion.h"


bool BooleanQuestion::AskQuestion(std::string question) {
	while (true)
	{
		FrameController::FirstUpdate();
		Mouse::Update();

		Vector2 size = Vector2(300, 50);
		Rect r2 = Rect(Vector2(10, 10), size);
		Rect r1 = Rect(Vector2(SDLClass::GetScreenSizeVector2() / 2 - size / 2), size);
		TextBox textbox(Vector2(2, 2), r1, Color(0));
		textbox.displayText.text = question;
		textbox.displayText.size = 15;
		textbox.alineo = TextBox::ALIN_CENTERED;

		Vector2 buttonSize = Vector2(40,15);
		StandardOption a = StandardOption(Rect::GetRectFromCenter(SDLClass::GetScreenSizeVector2()/2 + Vector2(-50,10),buttonSize),Text("Si"));
		StandardOption b = StandardOption(Rect::GetRectFromCenter(SDLClass::GetScreenSizeVector2()/2 + Vector2(50, 10), buttonSize), Text("No"));

		
		
		SDLClass::Clear();
		textbox.Draw();
		bool ac = a.isColliding(Mouse::GetVector2Pos());
		bool bc = b.isColliding(Mouse::GetVector2Pos());
		a.Draw(ac);
		b.Draw(bc);

		if (Mouse::leftClickPressed) {
			if (ac)
				return true;
			if (bc)
				return false;
		}


		SDL_SetRenderDrawColor(SDLClass::renderer, 0, 0, 0, 0);
		SDL_RenderPresent(SDLClass::renderer);

		FrameController::LateUpdate();
	}
}