// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIStats.h"
#include "SlateBasics.h"
#include "SlateExtras.h"

class SMenuWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMenuWidget) {}

		SLATE_ARGUMENT(TWeakObjectPtr<class ASandboxHUD>, OwningHud)
		SLATE_ARGUMENT(FGeneralStats, Stats)

	SLATE_END_ARGS()

	void Construct(const FArguments& args);

	TWeakObjectPtr<class ASandboxHUD> OwningHud;

	virtual bool SupportsKeyboardFocus() const override { return true; };
};
