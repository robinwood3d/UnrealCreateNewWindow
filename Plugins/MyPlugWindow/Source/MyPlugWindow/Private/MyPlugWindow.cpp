// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlugWindow.h"
#include "Widgets/SWindow.h"
#include "Widgets/SViewport.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AMyPlugWindow::AMyPlugWindow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AMyPlugWindow::SetContent(UUserWidget* Widget)
{
	if (Widget)
	{
		MyWindow->SetContent(Widget->TakeWidget());
		MyWidget = Widget;
	}
}

// Called when the game starts or when spawned
void AMyPlugWindow::BeginPlay()
{
	Super::BeginPlay();

	MyWindow = SNew(SWindow)
		.Type(EWindowType::Normal)
		.Style(&FCoreStyle::Get().GetWidgetStyle<FWindowStyle>("Window"))
		.Title(Title)
		.bDragAnywhere(bDragAnywhere)
		.AutoCenter(static_cast<EAutoCenter>(CenterMode))
		.ScreenPosition(Position)
		.ClientSize(Size)
		.AdjustInitialSizeAndPositionForDPIScale(true)
		.SupportsTransparency(EWindowTransparency::None)
		.InitialOpacity(1.f)
		.IsInitiallyMaximized(false)
		.IsInitiallyMinimized(false)
		.SizingRule(static_cast<ESizingRule>(SizingMode))
		.IsPopupWindow(false)
		.IsTopmostWindow(true)
		.FocusWhenFirstShown(true)
		.ActivationPolicy(EWindowActivationPolicy::Always)
		.UseOSWindowBorder(bUseOSWindowBorder)
		.HasCloseButton(bHasCloseButton)
		.SupportsMaximize(bSupportsMaximize)
		.SupportsMinimize(bSupportsMinimize)
		.ShouldPreserveAspectRatio(false)
		.CreateTitleBar(bCreateTitleBar)
		.SaneWindowPlacement(true)
		.LayoutBorder(FMargin(0, 0, 0, 0))
		.UserResizeBorder(FMargin(5, 5, 5, 5))
		.bManualManageDPI(false);

	if (MyWindow.IsValid())
	{
		if (MyWidget)
		{
			MyWindow->SetContent(MyWidget->TakeWidget());
		}

		FSlateApplication::Get().AddWindow(MyWindow.ToSharedRef(), true);
		MyWindow->GetOnWindowClosedEvent().AddLambda([this](const TSharedRef<SWindow>& Window) {Destroy(); });
	}
}

void AMyPlugWindow::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (MyWindow.IsValid())
	{
		MyWindow->GetOnWindowClosedEvent().RemoveAll(this);
		MyWindow->RequestDestroyWindow();
		//MyWindow->DestroyWindowImmediately();
	}
}

// Called every frame
void AMyPlugWindow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

