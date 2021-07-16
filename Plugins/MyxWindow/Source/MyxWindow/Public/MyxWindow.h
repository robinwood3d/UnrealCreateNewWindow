// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyxWindow.generated.h"

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

UCLASS()
class MYXWINDOW_API AMyxWindow : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyxWindow();

	UFUNCTION(BlueprintCallable, Category = "MyxWindow")
	void SetContent(UUserWidget* Widget);

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FText Title;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	bool bDragAnywhere = true;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	ECenterMode CenterMode = ECenterMode::None;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FVector2D Position;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FVector2D Size;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	ESizingMode SizingMode = ESizingMode::Autosized;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	bool bUseOSWindowBorder = false;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	bool bHasCloseButton = false;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	bool bSupportsMaximize = false;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	bool bSupportsMinimize = false;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	bool bCreateTitleBar = false;

	/** 保存一个窗口内控件的指针*/
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	UUserWidget* MyWidget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void EndPlay(const EEndPlayReason::Type EndPlayReason);

	/** 在这个对象里保存这个SWindow对象的指针*/
	TSharedPtr<SWindow> MyWindow;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
