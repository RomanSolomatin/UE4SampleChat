// Copyright ZX.Diablo 2017

#pragma once

#include "CoreMinimal.h"
#include "Online.h"
#include "GameFramework/GameSession.h"
#include "UE4SampleChatGameSession.generated.h"

/**
 * 
 */
UCLASS()
class UE4SAMPLECHAT_API AUE4SampleChatGameSession : public AGameSession
{
	GENERATED_BODY()
	
public:
	AUE4SampleChatGameSession ();

public:
	/**
	 * Create new session
	 * @param UserId User ID
	 * @param SessionName Session name
	 * @param MaxClients Maximum public clients allowed
	 * @return Success flag
	 */
	bool HostSession (const FUniqueNetId& UserId, FName SessionName, int32 MaxClients);

	/**
	 * Find session to join
	 * @param UserId Searching user ID
	 * @return Success flag
	 */
	bool FindSession (const FUniqueNetId& UserId);

	/**
	 * Join session
	 * @param UserId User ID
	 * @param SessionName Session name
	 * @param SearchResult Found session info
	 * @return Success flag
	 */
	bool JoinSession (const FUniqueNetId& UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult);

public:
	/**
	 * Event triggered when session is created and started
	 */
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSessionReady, FName, bool);
	typedef FOnSessionReady::FDelegate FOnSessionReadyDelegate;

	/**
	 * Event triggered when session is found
	 */
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSessionFound, const FOnlineSessionSearchResult&, bool);
	typedef FOnSessionFound::FDelegate FOnSessionFoundDelegate;

	/**
	 * Event triggered after session is joined
	 */
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSessionJoined, const FString&, EOnJoinSessionCompleteResult::Type);
	typedef FOnSessionJoined::FDelegate FOnSessionJoinedDelegate;

	/**
	 * Delegate fired when session is created and started
	 * @param SessionName Session name
	 * @param bWasSuccessful Success flag
	 */
	DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnSessionReady, FName, bool);

	/**
	 * Delegate fired when session is found
	 * @param SearchResult Found session info (the first one)
	 * @param bWasSuccessful Success flag
	 */
	DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnSessionFound, const FOnlineSessionSearchResult&, bool);

	/**
	 * Delegate fired after session is joined
	 * @param URL URL to join
	 * @param Result Join result type
	 */
	DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnSessionJoined, const FString&, EOnJoinSessionCompleteResult::Type);

private:
	void OnCreateSessionComplete (FName SessionName, bool bWasSuccessful);
	void OnStartSessionComplete (FName SessionName, bool bWasSuccessful);
	void OnFindSessionsComplete (bool bWasSuccessful);
	void OnJoinSessionComplete (FName SessionName, EOnJoinSessionCompleteResult::Type Result);

private:
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;

	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;
	FDelegateHandle OnFindSessionsCompleteDelegateHandle;
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;

	TSharedPtr<FOnlineSessionSearch> SessionSearch;
};
