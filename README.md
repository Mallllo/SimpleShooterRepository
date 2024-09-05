# 클래스 구조도
```mermaid
%%{
  init: {
    'theme': 'base',
    'themeVariables': {
      'primaryColor': '#ffd700',
      'lineColor':'#ffd700'
    }
  }
}%%
graph TD;
    ACharacter-->AShooterCharacter;
    APlayerController-->AShooterPlayerController;
    AAIController-->AShooterAIController;
```
```mermaid
%%{
  init: {
    'theme': 'base',
    'themeVariables': {
      'primaryColor': '#00ff7f',
      'lineColor':'#00ff7f'
    }
  }
}%%
graph TD;
    AActor-->AGun;
    AGun-->ARifle;
    AGun-->ALauncher;
    AActor-->AProjectile;
```
```mermaid
%%{
  init: {
    'theme': 'base',
    'themeVariables': {
      'primaryColor': '#e34234',
      'lineColor':'#e34234'
    }
  }
}%%
graph TD;
    AActor-->ACollectable;
    ACollectable-->ACollectableAmmo;
```
```mermaid
%%{
  init: {
    'theme': 'base',
    'themeVariables': {
      'primaryColor': '#007fff',
      'lineColor':'#007fff'
    }
  }
}%%
graph TD;
    AGameModeBase-->ASimpleShooterGameModeBase;
    ASimpleShooterGameModeBase-->AKillEmAllGameModeBase;
```
```mermaid
%%{
  init: {
    'theme': 'base',
    'themeVariables': {
      'primaryColor': '#18dffc',
      'lineColor':'#18dffc'
    }
  }
}%%
graph TD;
    UBTTaskNode-->UBTTask_Shoot;
    UBTTask_BlackboardBase-->UBTTask_ClearBlackboardValue;
    UBTService_BlackboardBase-->UBTService_PlayerLocation;
    UBTService_BlackboardBase-->UBTService_PlayerLocationIfSeen;
    UBTService_BlackboardBase-->UBTService_LastKnownLocation;
```
