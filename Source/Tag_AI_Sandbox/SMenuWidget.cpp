// Fill out your copyright notice in the Description page of Project Settings.


#include "SMenuWidget.h"

#define LOCTEXT_NAMESPACE "MenuWidget"

void SMenuWidget::Construct(const FArguments& args)
{
	FGeneralStats StatsData = args._Stats;

	FText TotalEntities = FText::Format(LOCTEXT("TotalEntities", "Total Entities: {0}"), StatsData.totalEntities);
	FText TotalTeams = FText::Format(LOCTEXT("TotalTeams", "Total Teams: {0}"), StatsData.totalTeams);
	FText CurrentGeneration = FText::Format(LOCTEXT("CurrentGeneration", "Generation: {0}"), StatsData.generation);
	FText TeamSection = LOCTEXT("TeamSection", "\n----- Teams ------");
	TSharedPtr<SVerticalBox> TeamsBox = SNew(SVerticalBox);

	const FMargin ContentPadding = FMargin(10);
	const FSlateFontInfo DataSlot = FCoreStyle::GetDefaultFontStyle("Regular", 20);

	for (auto curr : StatsData.Entities)
	{
		FText CurrentTeam = FText::Format(LOCTEXT("CurrentTeam", " > {0}: {1}"), FText::FromString(curr.Key), curr.Value);
		
		TeamsBox->AddSlot()
		[
			SNew(STextBlock).Text(CurrentTeam).Font(DataSlot)
		];
	}

	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill).Padding(ContentPadding)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot().AutoHeight()
			[
				SNew(STextBlock).Text(CurrentGeneration).Font(DataSlot)
			]
			+ SVerticalBox::Slot().AutoHeight()
			[
				SNew(STextBlock).Text(TotalEntities).Font(DataSlot)
			]
			+ SVerticalBox::Slot().AutoHeight()
			[
				SNew(STextBlock).Text(TotalTeams).Font(DataSlot)
			]
			+ SVerticalBox::Slot().AutoHeight()
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot().AutoHeight()
				[
					SNew(STextBlock).Text(TeamSection).Font(DataSlot)
				]
				+ SVerticalBox::Slot().AutoHeight()
				[
					TeamsBox.ToSharedRef()
				]
			]
		]
	];
}

#undef LOCTEXT_NAMESPACE
