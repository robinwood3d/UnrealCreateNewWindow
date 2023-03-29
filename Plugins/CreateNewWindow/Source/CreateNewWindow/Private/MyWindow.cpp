// Copyright MytaGames. All Rights Reserved.


#include "MyWindow.h"
#include "Widgets/SWindow.h"
#include "Blueprint/UserWidget.h"
#include "Framework/Application/SlateApplication.h"
#include "GenericPlatform/GenericWindowDefinition.h"

UMyWindow* UMyWindow::SpawnWindow(FMyWindowSettings Settings, UUserWidget* Content, UObject* Outer)
{
	UMyWindow* Window = NewObject<UMyWindow>(Outer);

	Window->SlateWindow = SNew(SWindow)
		.Title(Settings.Title)
		.bDragAnywhere(Settings.bDragAnywhere)
		.AutoCenter(static_cast<EAutoCenter>(Settings.CenterMode))
		.ScreenPosition(Settings.Position)
		.ClientSize(Settings.Size)
#if ALPHA_BLENDED_WINDOWS
		// 这个地方如果不这样设置, 在使用OSWindowsBorder的时候UMG会出现拖影
		.SupportsTransparency(EWindowTransparency::PerPixel)
#endif
		.IsInitiallyMaximized(Settings.bIsInitiallyMaximized)
		.SizingRule(static_cast<ESizingRule>(Settings.SizingMode))
		.UseOSWindowBorder(Settings.bUseOSWindowBorder)
		.HasCloseButton(Settings.bHasCloseButton)
		.SupportsMaximize(Settings.bSupportsMaximize)
		.SupportsMinimize(Settings.bSupportsMinimize)
		.CreateTitleBar(Settings.bCreateTitleBar);

	if (Window->SlateWindow.IsValid())
	{
		if (Content)
		{
			Window->SetContent(Content);
		}
		FSlateApplication::Get().AddWindow(Window->SlateWindow.ToSharedRef(), true);
		FSlateApplication::Get().GetRenderer()->CreateViewport(Window->SlateWindow.ToSharedRef());
	}

	return Window;
}

void UMyWindow::SetContent(UUserWidget* Widget)
{
	if (SlateWindow.IsValid() && IsValid(Widget))
	{
		SlateWindow->SetContent(Widget->TakeWidget());
	}
}

void UMyWindow::CloseWindow()
{
	if (SlateWindow.IsValid())
	{
		SlateWindow->RequestDestroyWindow();
		SlateWindow.Reset();
	}
}

void UMyWindow::BeginDestroy()
{
	CloseWindow();

	Super::BeginDestroy();
}
