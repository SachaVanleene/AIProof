# AIProof
Projet personnel sous Unreal Engine - C++ mettant en pratique des concepts de lindustrie lié à l AI ou au monde de la recherche

In progress : 
- Comprehension optimale de Unreal
  - GPP Framework
  - Engine FLow
  - Physique Engine
  - Anim Engine
- GOAP : 
  - Design Tech (Goap Action, GoapCondition, GoapEffet, Goap Goal)
  - Goal need a list of condition to be active and list of action to be fulfiil
  - Planner (Backward, A* heuristic)
  - Watch out goal path should be 2 - 3 long - not to much logic in
  - (If needed rewatch the video : https://www.youtube.com/watch?v=gm7K68663rA)

- Steering : 
  - Fonctionnel, mais choix de savoir si fonctionne avec UcharacterMovementCOmponent ou pas (Car chose a revoir + Friction issue)
  - Ajout steering avec offset
  - Choisir une solution elegante pour mixer avec la navig (Steering follow path  ??)
- BT : 
  - FInir correctement le BT du guarde en cours (Systeme de combat a faire plus tard pas priorite)
- Neural Network : 
  - Pour le moment dev sur un projet console, portage sous projet et choisir appliquation
- Anim : 
  - Utiliser une FSM correct et un code driven (skip for now car pas le main focus)
- Visual Detection YSstem : 
  - Working
  - Need to check distance and raycast to check if we do not collide with other things meaning we dont see through wall
- General : 
  - Clean le code et restructure avec Steering
  
  
 MUST HAVE : 
- Project Style :
   - Clean les fichiers
   - Changer les modeles pour des araignees
   - Adapter Terrain
   - Sous diviser terrain en experiment Field
 - AI : 
   - ORCA Fonctionnel (Voir si from scracth ou partir d une lib, conprehension dalgo done)
   - GOAP (From scratch, todo )
   - NavMesh (Auto creation algorithm + A* from scracth, utilise le systeme d Unreal for now car pas main focus et deja balaye
    sur d autres projets)
   - FuzzyLogic (Adapter travaux deja faits sous unreal)
    
    
  NICE TO HAVE : 
 - Systeme de combat (GPP)
 - UI choose Proof to see
