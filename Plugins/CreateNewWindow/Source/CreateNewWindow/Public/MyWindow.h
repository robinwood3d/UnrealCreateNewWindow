// Copyright MytaGames. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyWindow.generated.h"

class SWindow;
class UUserWidget;

UENUM(BlueprintType)
enum class ESizingMode : uint8
{
	/* The windows size fixed and cannot be resized **/
	FixedSize,

	/** The window size is computed from its content and cannot be resized by users */
	Autosized,

	/** The window can be resized by users */
	UserSized
};

UENUM(BlueprintType)
enum class ECenterMode : uint8
{
	/** Don't auto-center the window */
	None,

	/** Auto-center the window on the primary work area */
	PrimaryWorkArea,

	/** Auto-center the window on the preferred work area, determined using GetPreferredWorkArea() */
	PreferredWorkArea,
};

USTRUCT(BlueprintType)
struct FMyWindowSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CreateNewWindow|MyWindow")
		FText Title = FText::FromString("MyWindow");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CreateNewWindow|MyWindow")
		bool bDragAnywhere = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CreateNewWindow|MyWindow")
		ECenterMode CenterMode = ECenterMode::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CreateNewWindow|MyWindow")
		FVector2D Position = FVector2D(0, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CreateNewWindow|MyWindow")
		FVector2D Size = FVector2D(400, 300);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CreateNewWindow|MyWindow")
		bool bIsInitiallyMaximized = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CreateNewWindow|MyWindow")
		ESizingMode SizingMode = ESizingMode::Autosized;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CreateNewWindow|MyWindow")
		bool bUseOSWindowBorder = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CreateNewWindow|MyWindow")
		bool bHasCloseButton = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CreateNewWindow|MyWindow")
		bool bSupportsMaximize = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CreateNewWindow|MyWindow")
		bool bSupportsMinimize = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CreateNewWindow|MyWindow")
		bool bCreateTitleBar = true;
};

/**
 *
 */
UCLASS(BlueprintType)
class CREATENEWWINDOW_API UMyWindow : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Window"), Category = "CreateNewWindow|MyWindow")
		static UMyWindow* SpawnWindow(FMyWindowSettings Settings, UUserWidget* Content, UObject* Outer);

	UFUNCTION(BlueprintCallable, Category = "CreateNewWindow|MyWindow")
		void SetContent(UUserWidget* Widget);

	UFUNCTION(BlueprintCallable, Category = "CreateNewWindow|MyWindow")
		void CloseWindow();

	virtual void BeginDestroy()override;

protected:
	TSharedPtr<SWindow> SlateWindow = nullptr;

};