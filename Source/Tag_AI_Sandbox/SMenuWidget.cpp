// Fill out your copyright notice in the Description page of Project Settings.


#include "SMenuWidget.h"

#include "Kismet/GameplayStatics.h"

#define LOCTEXT_NAMESPACE "MenuWidget"

void SMenuWidget::Construct(const FArguments& args)
{
	const FMargin ContentPadding = FMargin(10);
	int totalPawns = args._TotalPawns;
	FText TitleText = FText::Format(LOCTEXT("GeneratioCount", "Total Entities: {0}"), totalPawns);

	const FSlateFontInfo TotalPlayers = FCoreStyle::GetDefaultFontStyle("Regular", 20);
	
	ChildSlot
	[
		SNew(SOverlay) + SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill).Padding(ContentPadding)
		[
			SNew(SVerticalBox) + SVerticalBox::Slot()
			[
				SNew(STextBlock).Text(TitleText).Font(TotalPlayers)
			]
		]
	];
}

#undef LOCTEXT_NAMESPACE