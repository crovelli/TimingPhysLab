#include "TimingEventAction.hh"
#include "TimingAnalysisManager.hh"
#include "TimingRun.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

TimingEventAction::TimingEventAction()
  : G4UserEventAction(),
    fEdep1(0.),
    fEdep2(0.)
{} 

TimingEventAction::~TimingEventAction()
{}

void TimingEventAction::BeginOfEventAction(const G4Event*)
{    
  fEdep1 = 0.;
  fEdep2 = 0.;

  TimingAnalysisManager::GetInstance()->BeginOfEvent();
}

void TimingEventAction::EndOfEventAction(const G4Event* evt)
{   
  // accumulate statistics in TimingRun                                                   
  TimingRun* run = static_cast<TimingRun*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  run->AddEdep1(fEdep1);
  run->AddEdep2(fEdep2);
  
  // for histos
  TimingAnalysisManager::GetInstance()->EndOfEvent();
}
