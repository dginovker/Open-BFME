// cl: /EHsc /ICode/Libraries/Source/WWVegas/WWLib
#include "module_factory.h"

// Masked DIR32 targets: distinct symbols so each createProc/createDataProc/
// field8 store stays an independent immediate the build copies from the target.
extern "C" {
    int cp000; int dp000; int cp001; int dp001; int cp002; int dp002;
    int cp003; int dp003; int cp004; int dp004; int cp005; int dp005;
    int cp006; int dp006; int cp007; int dp007; int cp008; int dp008;
    int cp009; int dp009; int cp010; int dp010; int cp011; int dp011;
    int cp012; int dp012; int cp013; int dp013; int cp014; int dp014;
    int cp015; int dp015; int cp016; int dp016; int cp017; int dp017;
    int cp018; int dp018; int cp019; int dp019; int cp020; int dp020;
    int cp021; int dp021; int cp022; int dp022; int cp023; int dp023;
    int cp024; int dp024; int cp025; int dp025; int cp026; int dp026;
    int cp027; int dp027; int cp028; int dp028; int cp029; int dp029;
    int cp030; int dp030; int cp031; int dp031; int fd031; int cp032;
    int dp032; int fd032; int cp033; int dp033; int fd033; int cp034;
    int dp034; int cp035; int dp035; int fd035; int cp036; int dp036;
    int cp037; int dp037; int cp038; int dp038; int cp039; int dp039;
    int cp040; int dp040; int cp041; int dp041; int cp042; int dp042;
    int cp043; int dp043; int cp044; int dp044; int cp045; int dp045;
    int cp046; int dp046; int cp047; int dp047; int cp048; int dp048;
    int cp049; int dp049; int cp050; int dp050; int cp051; int dp051;
    int cp052; int dp052; int cp053; int dp053; int cp054; int dp054;
    int cp055; int dp055; int cp056; int dp056; int cp057; int dp057;
    int cp058; int dp058; int cp059; int dp059; int cp060; int dp060;
    int cp061; int dp061; int cp062; int dp062; int cp063; int dp063;
    int cp064; int dp064; int cp065; int dp065; int cp066; int dp066;
    int cp067; int dp067; int cp068; int dp068; int cp069; int dp069;
    int cp070; int dp070; int cp071; int dp071; int cp072; int dp072;
    int cp073; int dp073; int cp074; int dp074; int cp075; int dp075;
    int cp076; int dp076; int cp077; int dp077; int cp078; int dp078;
    int cp079; int dp079; int cp080; int dp080; int cp081; int dp081;
    int cp082; int dp082; int cp083; int dp083; int cp084; int dp084;
    int cp085; int dp085; int cp086; int dp086; int cp087; int dp087;
    int cp088; int dp088; int cp089; int dp089; int cp090; int dp090;
    int cp091; int dp091; int cp092; int dp092; int cp093; int dp093;
    int cp094; int dp094; int cp095; int dp095; int cp096; int dp096;
    int cp097; int dp097; int cp098; int dp098; int cp099; int dp099;
    int cp100; int dp100; int cp101; int dp101; int cp102; int dp102;
    int cp103; int dp103; int cp104; int dp104; int cp105; int dp105;
    int cp106; int dp106; int cp107; int dp107; int cp108; int dp108;
    int cp109; int dp109; int cp110; int dp110; int cp111; int dp111;
    int cp112; int dp112; int cp113; int dp113; int cp114; int dp114;
    int cp115; int dp115; int cp116; int dp116; int cp117; int dp117;
    int cp118; int dp118; int cp119; int dp119; int cp120; int dp120;
    int cp121; int dp121; int cp122; int dp122; int cp123; int dp123;
    int cp124; int dp124; int cp125; int dp125; int cp126; int dp126;
    int cp127; int dp127; int cp128; int dp128; int cp129; int dp129;
    int cp130; int dp130; int cp131; int dp131; int cp132; int dp132;
    int cp133; int dp133; int cp134; int dp134; int cp135; int dp135;
    int cp136; int dp136; int cp137; int dp137; int cp138; int dp138;
    int cp139; int dp139; int cp140; int dp140; int cp141; int dp141;
    int cp142; int dp142; int cp143; int dp143; int cp144; int dp144;
    int cp145; int dp145; int cp146; int dp146; int cp147; int dp147;
    int cp148; int dp148; int cp149; int dp149; int cp150; int dp150;
    int cp151; int dp151; int cp152; int dp152; int cp153; int dp153;
    int cp154; int dp154; int cp155; int dp155; int cp156; int dp156;
    int cp157; int dp157; int cp158; int dp158; int cp159; int dp159;
    int cp160; int dp160; int cp161; int dp161; int cp162; int dp162;
    int cp163; int dp163; int cp164; int dp164; int cp165; int dp165;
    int cp166; int dp166; int cp167; int dp167; int cp168; int dp168;
    int cp169; int dp169; int cp170; int dp170; int cp171; int dp171;
    int cp172; int dp172; int cp173; int dp173; int cp174; int dp174;
    int cp175; int dp175; int cp176; int dp176; int cp177; int dp177;
    int cp178; int dp178; int cp179; int dp179; int cp180; int dp180;
    int cp181; int dp181; int cp182; int dp182; int cp183; int dp183;
    int cp184; int dp184; int cp185; int dp185; int cp186; int dp186;
    int cp187; int dp187; int cp188; int dp188; int cp189; int dp189;
    int cp190; int dp190; int cp191; int dp191; int cp192; int dp192;
    int cp193; int dp193; int cp194; int dp194; int cp195; int dp195;
    int cp196; int dp196; int cp197; int dp197; int cp198; int dp198;
    int cp199; int dp199; int cp200; int dp200; int cp201; int dp201;
    int cp202; int dp202; int cp203; int dp203; int cp204; int dp204;
    int cp205; int dp205; int cp206; int dp206; int cp207; int dp207;
    int cp208; int dp208; int cp209; int dp209; int cp210; int dp210;
    int cp211; int dp211; int cp212; int dp212; int cp213; int dp213;
    int cp214; int dp214; int cp215; int dp215; int cp216; int dp216;
    int cp217; int dp217; int cp218; int dp218; int cp219; int dp219;
    int cp220; int dp220; int cp221; int dp221; int cp222; int dp222;
    int cp223; int dp223; int cp224; int dp224; int cp225; int dp225;
    int cp226; int dp226; int cp227; int dp227; int cp228; int dp228;
    int cp229; int dp229; int cp230; int dp230; int cp231; int dp231;
    int cp232; int dp232; int cp233; int dp233; int cp234; int dp234;
    int cp235; int dp235; int cp236; int dp236; int cp237; int dp237;
    int cp238; int dp238; int cp239; int dp239; int cp240; int dp240;
    int cp241; int dp241; int cp242; int dp242; int cp243; int dp243;
    int cp244; int dp244; int cp245; int dp245; int cp246; int dp246;
}

void ModuleFactory::addModuleInternal(const void *proc, const void *dataproc,
     const void *data, ModuleType type, const AsciiString &name, int whichIntf)
{
    NameKeyType namekey = makeDecoratedNameKey(name, type);
    ModuleTemplate &mtm = m_moduleTemplateMap[namekey];
    mtm.m_createProc = proc;
    mtm.m_createDataProc = dataproc;
    mtm.m_whichInterfaces = whichIntf;
    mtm.m_data = data;
}

void ModuleFactory::init(void)
{
    {
        AsciiString nm("AutoHealBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp000;
        mtm.m_createDataProc = &dp000;
        mtm.m_whichInterfaces = 133;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("GettingBuiltBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp001;
        mtm.m_createDataProc = &dp001;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("CastleBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp002;
        mtm.m_createDataProc = &dp002;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("CastleMemberBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp003;
        mtm.m_createDataProc = &dp003;
        mtm.m_whichInterfaces = 4;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("BuildingBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp004;
        mtm.m_createDataProc = &dp004;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("BridgeBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp005;
        mtm.m_createDataProc = &dp005;
        mtm.m_whichInterfaces = 7;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("BridgeScaffoldBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp006;
        mtm.m_createDataProc = &dp006;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("BridgeTowerBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp007;
        mtm.m_createDataProc = &dp007;
        mtm.m_whichInterfaces = 6;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("RampageBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp008;
        mtm.m_createDataProc = &dp008;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("EnragedBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp009;
        mtm.m_createDataProc = &dp009;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("EntEnragedUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp010;
        mtm.m_createDataProc = &dp010;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("HitReactionBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp011;
        mtm.m_createDataProc = &dp011;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("ClickReactionBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp012;
        mtm.m_createDataProc = &dp012;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("SiegeDockingBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp013;
        mtm.m_createDataProc = &dp013;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("AutoAbilityBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp014;
        mtm.m_createDataProc = &dp014;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("DualWeaponBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp015;
        mtm.m_createDataProc = &dp015;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("AimWeaponBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp016;
        mtm.m_createDataProc = &dp016;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("BezierProjectileBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp017;
        mtm.m_createDataProc = &dp017;
        mtm.m_whichInterfaces = 17;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("PhysicsBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp018;
        mtm.m_createDataProc = &dp018;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("InstantDeathBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp019;
        mtm.m_createDataProc = &dp019;
        mtm.m_whichInterfaces = 2;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("SlowDeathBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp020;
        mtm.m_createDataProc = &dp020;
        mtm.m_whichInterfaces = 3;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("SpawnBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp021;
        mtm.m_createDataProc = &dp021;
        mtm.m_whichInterfaces = 135;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("GiantBirdSlowDeathBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp022;
        mtm.m_createDataProc = &dp022;
        mtm.m_whichInterfaces = 3;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("CaveContain");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp023;
        mtm.m_createDataProc = &dp023;
        mtm.m_whichInterfaces = 95;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("OpenContain");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp024;
        mtm.m_createDataProc = &dp024;
        mtm.m_whichInterfaces = 95;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("SpawnUnitBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp025;
        mtm.m_createDataProc = &dp025;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("OathbreakersFadeAwayBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp026;
        mtm.m_createDataProc = &dp026;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("WargBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp027;
        mtm.m_createDataProc = &dp027;
        mtm.m_whichInterfaces = 0;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("DynamicPortalBehaviour");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp028;
        mtm.m_createDataProc = &dp028;
        mtm.m_whichInterfaces = 142;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("CritterEmitterUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp029;
        mtm.m_createDataProc = &dp029;
        mtm.m_whichInterfaces = 17;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("HealContain");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp030;
        mtm.m_createDataProc = &dp030;
        mtm.m_whichInterfaces = 95;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("HordeContain");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp031;
        mtm.m_createDataProc = &dp031;
        mtm.m_whichInterfaces = 95;
        mtm.m_data = &fd031;
    }
    {
        AsciiString nm("HorseHordeContain");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp032;
        mtm.m_createDataProc = &dp032;
        mtm.m_whichInterfaces = 95;
        mtm.m_data = &fd032;
    }
    {
        AsciiString nm("AODHordeContain");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp033;
        mtm.m_createDataProc = &dp033;
        mtm.m_whichInterfaces = 95;
        mtm.m_data = &fd033;
    }
    {
        AsciiString nm("GarrisonContain");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp034;
        mtm.m_createDataProc = &dp034;
        mtm.m_whichInterfaces = 95;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("TransportContain");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp035;
        mtm.m_createDataProc = &dp035;
        mtm.m_whichInterfaces = 95;
        mtm.m_data = &fd035;
    }
    {
        AsciiString nm("SiegeEngineContain");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp036;
        mtm.m_createDataProc = &dp036;
        mtm.m_whichInterfaces = 95;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("HordeSiegeEngineContain");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp037;
        mtm.m_createDataProc = &dp037;
        mtm.m_whichInterfaces = 95;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("TunnelContain");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp038;
        mtm.m_createDataProc = &dp038;
        mtm.m_whichInterfaces = 95;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("HordeTransportContain");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp039;
        mtm.m_createDataProc = &dp039;
        mtm.m_whichInterfaces = 95;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("HordeGarrisonContain");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp040;
        mtm.m_createDataProc = &dp040;
        mtm.m_whichInterfaces = 95;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("ContestableContain");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp041;
        mtm.m_createDataProc = &dp041;
        mtm.m_whichInterfaces = 95;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("RiderChangeContain");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp042;
        mtm.m_createDataProc = &dp042;
        mtm.m_whichInterfaces = 95;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("SlaughterHordeContain");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp043;
        mtm.m_createDataProc = &dp043;
        mtm.m_whichInterfaces = 95;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("PropagandaTowerBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp044;
        mtm.m_createDataProc = &dp044;
        mtm.m_whichInterfaces = 3;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("FireWeaponWhenDamagedBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp045;
        mtm.m_createDataProc = &dp045;
        mtm.m_whichInterfaces = 133;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("FireWeaponWhenDeadBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp046;
        mtm.m_createDataProc = &dp046;
        mtm.m_whichInterfaces = 131;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("PoisonedBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp047;
        mtm.m_createDataProc = &dp047;
        mtm.m_whichInterfaces = 5;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("SupplyWarehouseCripplingBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp048;
        mtm.m_createDataProc = &dp048;
        mtm.m_whichInterfaces = 5;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("ClearanceTestingSlowDeathBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp049;
        mtm.m_createDataProc = &dp049;
        mtm.m_whichInterfaces = 3;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("RunOffMapBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp050;
        mtm.m_createDataProc = &dp050;
        mtm.m_whichInterfaces = 0;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("ReplenishUnitsBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp051;
        mtm.m_createDataProc = &dp051;
        mtm.m_whichInterfaces = 129;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("SlaveWatcherBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp052;
        mtm.m_createDataProc = &dp052;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("DestroyDie");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp053;
        mtm.m_createDataProc = &dp053;
        mtm.m_whichInterfaces = 2;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("FXListDie");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp054;
        mtm.m_createDataProc = &dp054;
        mtm.m_whichInterfaces = 2;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("CrushDie");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp055;
        mtm.m_createDataProc = &dp055;
        mtm.m_whichInterfaces = 2;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("HeroDie");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp056;
        mtm.m_createDataProc = &dp056;
        mtm.m_whichInterfaces = 2;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("CreateCrateDie");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp057;
        mtm.m_createDataProc = &dp057;
        mtm.m_whichInterfaces = 2;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("RefundDie");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp058;
        mtm.m_createDataProc = &dp058;
        mtm.m_whichInterfaces = 2;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("CreateObjectDie");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp059;
        mtm.m_createDataProc = &dp059;
        mtm.m_whichInterfaces = 2;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("SpecialPowerCompletionDie");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp060;
        mtm.m_createDataProc = &dp060;
        mtm.m_whichInterfaces = 2;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("UpgradeDie");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp061;
        mtm.m_createDataProc = &dp061;
        mtm.m_whichInterfaces = 2;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("KeepObjectDie");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp062;
        mtm.m_createDataProc = &dp062;
        mtm.m_whichInterfaces = 2;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("AssistedTargetingUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp063;
        mtm.m_createDataProc = &dp063;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("AutoFindHealingUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp064;
        mtm.m_createDataProc = &dp064;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("StealthDetectorUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp065;
        mtm.m_createDataProc = &dp065;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("BroadcastStealthUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp066;
        mtm.m_createDataProc = &dp066;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("StealthUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp067;
        mtm.m_createDataProc = &dp067;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("DelayedWeaponSetUpgradeUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp068;
        mtm.m_createDataProc = &dp068;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("DeletionUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp069;
        mtm.m_createDataProc = &dp069;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("DynamicShroudClearingRangeUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp070;
        mtm.m_createDataProc = &dp070;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("DeployStyleAIUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp071;
        mtm.m_createDataProc = &dp071;
        mtm.m_whichInterfaces = 17;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("AssaultTransportAIUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp072;
        mtm.m_createDataProc = &dp072;
        mtm.m_whichInterfaces = 17;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("GiantBirdAIUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp073;
        mtm.m_createDataProc = &dp073;
        mtm.m_whichInterfaces = 17;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("LargeGroupBonusUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp074;
        mtm.m_createDataProc = &dp074;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("ToppleUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp075;
        mtm.m_createDataProc = &dp075;
        mtm.m_whichInterfaces = 17;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("DelayedLuaEventUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp076;
        mtm.m_createDataProc = &dp076;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("LifetimeUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp077;
        mtm.m_createDataProc = &dp077;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("OneRingPenaltyUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp078;
        mtm.m_createDataProc = &dp078;
        mtm.m_whichInterfaces = 3;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("SpecialEnemySenseUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp079;
        mtm.m_createDataProc = &dp079;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("RadiusDecalUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp080;
        mtm.m_createDataProc = &dp080;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("RainOfFireUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp081;
        mtm.m_createDataProc = &dp081;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("DestroyEnvironmentUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp082;
        mtm.m_createDataProc = &dp082;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("PartTheHeavensUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp083;
        mtm.m_createDataProc = &dp083;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("AutoDepositUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp084;
        mtm.m_createDataProc = &dp084;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("FireSpreadUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp085;
        mtm.m_createDataProc = &dp085;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("FireWeaponUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp086;
        mtm.m_createDataProc = &dp086;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("FlammableUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp087;
        mtm.m_createDataProc = &dp087;
        mtm.m_whichInterfaces = 5;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("FloatUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp088;
        mtm.m_createDataProc = &dp088;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("HeightDieUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp089;
        mtm.m_createDataProc = &dp089;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("SiegeAIUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp090;
        mtm.m_createDataProc = &dp090;
        mtm.m_whichInterfaces = 17;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("AIUpdateInterface");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp091;
        mtm.m_createDataProc = &dp091;
        mtm.m_whichInterfaces = 17;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("HordeAIUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp092;
        mtm.m_createDataProc = &dp092;
        mtm.m_whichInterfaces = 17;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("HordeWorkerAIUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp093;
        mtm.m_createDataProc = &dp093;
        mtm.m_whichInterfaces = 17;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("SupplyTruckAIUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp094;
        mtm.m_createDataProc = &dp094;
        mtm.m_whichInterfaces = 17;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("LaserUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 2);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp095;
        mtm.m_createDataProc = &dp095;
        mtm.m_whichInterfaces = 2048;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("CommandButtonHuntUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp096;
        mtm.m_createDataProc = &dp096;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("DemoTrapUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp097;
        mtm.m_createDataProc = &dp097;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("AutoPickUpUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp098;
        mtm.m_createDataProc = &dp098;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("CivilianSpawnUpdate");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp099;
        mtm.m_createDataProc = &dp099;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    {
        AsciiString nm("ShareExperienceBehavior");
        NameKeyType k = makeDecoratedNameKey(nm, 0);
        ModuleTemplate &mtm = m_moduleTemplateMap[k];
        mtm.m_createProc = &cp100;
        mtm.m_createDataProc = &dp100;
        mtm.m_whichInterfaces = 1;
        mtm.m_data = 0;
    }
    addModuleInternal(&cp101, &dp101, 0, 0, AsciiString("BannerCarrierUpdate"), 1);
    addModuleInternal(&cp102, &dp102, 0, 0, AsciiString("BattlePlanUpdate"), 1);
    addModuleInternal(&cp103, &dp103, 0, 0, AsciiString("GateOpenAndCloseBehavior"), 17);
    addModuleInternal(&cp104, &dp104, 0, 0, AsciiString("GateProxyBehavior"), 17);
    addModuleInternal(&cp105, &dp105, 0, 0, AsciiString("QueueProductionExitUpdate"), 1);
    addModuleInternal(&cp106, &dp106, 0, 0, AsciiString("RepairDockUpdate"), 1);
    addModuleInternal(&cp107, &dp107, 0, 0, AsciiString("ArrowStormUpdate"), 1);
    addModuleInternal(&cp108, &dp108, 0, 0, AsciiString("WeaponModeSpecialPowerUpdate"), 257);
    addModuleInternal(&cp109, &dp109, 0, 0, AsciiString("ModelConditionSpecialAbilityUpdate"), 1);
    addModuleInternal(&cp110, &dp110, 0, 0, AsciiString("ToggleMountedSpecialAbilityUpdate"), 9);
    addModuleInternal(&cp111, &dp111, 0, 0, AsciiString("ToggleHiddenSpecialAbilityUpdate"), 1);
    addModuleInternal(&cp112, &dp112, 0, 0, AsciiString("WeaponFireSpecialAbilityUpdate"), 1);
    addModuleInternal(&cp113, &dp113, 0, 0, AsciiString("HeroModeSpecialAbilityUpdate"), 1);
    addModuleInternal(&cp114, &dp114, 0, 0, AsciiString("WeaponSetSpecialAbilityUpdate"), 1);
    addModuleInternal(&cp115, &dp115, 0, 0, AsciiString("GiveUpgradeUpdate"), 1);
    addModuleInternal(&cp116, &dp116, 0, 0, AsciiString("LargeGroupAudioUpdate"), 1);
    addModuleInternal(&cp117, &dp117, 0, 0, AsciiString("DefaultProductionExitUpdate"), 1);
    addModuleInternal(&cp118, &dp118, 0, 0, AsciiString("SpawnPointProductionExitUpdate"), 1);
    addModuleInternal(&cp119, &dp119, 0, 0, AsciiString("SlavedUpdate"), 1);
    addModuleInternal(&cp120, &dp120, 0, 0, AsciiString("OCLUpdate"), 1);
    addModuleInternal(&cp121, &dp121, 0, 0, AsciiString("AttributeModifierAuraUpdate"), 129);
    addModuleInternal(&cp122, &dp122, 0, 0, AsciiString("SpecialAbilityUpdate"), 1);
    addModuleInternal(&cp123, &dp123, 0, 0, AsciiString("SupplyCenterProductionExitUpdate"), 1);
    addModuleInternal(&cp124, &dp124, 0, 0, AsciiString("SupplyCenterDockUpdate"), 1);
    addModuleInternal(&cp125, &dp125, 0, 0, AsciiString("SupplyWarehouseDockUpdate"), 1);
    addModuleInternal(&cp126, &dp126, 0, 0, AsciiString("MonsterDockUpdate"), 1);
    addModuleInternal(&cp127, &dp127, 0, 0, AsciiString("DozerAIUpdate"), 17);
    addModuleInternal(&cp128, &dp128, 0, 0, AsciiString("RousingSpeechUpdate"), 1);
    addModuleInternal(&cp129, &dp129, 0, 0, AsciiString("GloriousChargeUpdate"), 1);
    addModuleInternal(&cp130, &dp130, 0, 0, AsciiString("ProductionUpdate"), 3);
    addModuleInternal(&cp131, &dp131, 0, 0, AsciiString("ProneUpdate"), 1);
    addModuleInternal(&cp132, &dp132, 0, 0, AsciiString("HijackerUpdate"), 1);
    addModuleInternal(&cp133, &dp133, 0, 0, AsciiString("FadeAndDieOrnamentUpdate"), 1);
    addModuleInternal(&cp134, &dp134, 0, 0, AsciiString("StructureToppleUpdate"), 3);
    addModuleInternal(&cp135, &dp135, 0, 0, AsciiString("StructureCollapseUpdate"), 3);
    addModuleInternal(&cp136, &dp136, 0, 0, AsciiString("RubbleRiseUpdate"), 3);
    addModuleInternal(&cp137, &dp137, 0, 0, AsciiString("BoneFXUpdate"), 1);
    addModuleInternal(&cp138, &dp138, 0, 0, AsciiString("RadarUpdate"), 1);
    addModuleInternal(&cp139, &dp139, 0, 0, AsciiString("TransportAIUpdate"), 17);
    addModuleInternal(&cp140, &dp140, 0, 0, AsciiString("WanderAIUpdate"), 17);
    addModuleInternal(&cp141, &dp141, 0, 0, AsciiString("AnimalAIUpdate"), 17);
    addModuleInternal(&cp142, &dp142, 0, 0, AsciiString("FoundationAIUpdate"), 1);
    addModuleInternal(&cp143, &dp143, 0, 0, AsciiString("WorkerAIUpdate"), 17);
    addModuleInternal(&cp144, &dp144, 0, 0, AsciiString("WallUpgradeUpdate"), 5);
    addModuleInternal(&cp145, &dp145, 0, 0, AsciiString("DetachableRiderUpdate"), 1);
    addModuleInternal(&cp146, &dp146, 0, 0, AsciiString("RespawnUpdate"), 1);
    addModuleInternal(&cp147, &dp147, 0, 0, AsciiString("BloodthirstyUpdate"), 1);
    addModuleInternal(&cp148, &dp148, 0, 0, AsciiString("AttributeModifierPoolUpdate"), 1);
    addModuleInternal(&cp149, &dp149, 0, 0, AsciiString("SpecialDisguiseUpdate"), 9);
    addModuleInternal(&cp150, &dp150, 0, 0, AsciiString("EmotionTrackerUpdate"), 513);
    addModuleInternal(&cp151, &dp151, 0, 0, AsciiString("CostModifierUpgrade"), 140);
    addModuleInternal(&cp152, &dp152, 0, 0, AsciiString("ArmorUpgrade"), 132);
    addModuleInternal(&cp153, &dp153, 0, 0, AsciiString("BaseUpgrade"), 132);
    addModuleInternal(&cp154, &dp154, 0, 0, AsciiString("CommandSetUpgrade"), 132);
    addModuleInternal(&cp155, &dp155, 0, 0, AsciiString("DelayedUpgrade"), 132);
    addModuleInternal(&cp156, &dp156, 0, 0, AsciiString("LevelUpUpgrade"), 132);
    addModuleInternal(&cp157, &dp157, 0, 0, AsciiString("StatusBitsUpgrade"), 132);
    addModuleInternal(&cp158, &dp158, 0, 0, AsciiString("SubObjectsUpgrade"), 132);
    addModuleInternal(&cp159, &dp159, 0, 0, AsciiString("StealthUpgrade"), 132);
    addModuleInternal(&cp160, &dp160, 0, 0, AsciiString("RadarUpgrade"), 132);
    addModuleInternal(&cp161, &dp161, 0, 0, AsciiString("LocomotorSetUpgrade"), 132);
    addModuleInternal(&cp162, &dp162, 0, 0, AsciiString("ObjectCreationUpgrade"), 129);
    addModuleInternal(&cp163, &dp163, 0, 0, AsciiString("UnpauseSpecialPowerUpgrade"), 132);
    addModuleInternal(&cp164, &dp164, 0, 0, AsciiString("WeaponBonusUpgrade"), 132);
    addModuleInternal(&cp165, &dp165, 0, 0, AsciiString("WeaponSetUpgrade"), 132);
    addModuleInternal(&cp166, &dp166, 0, 0, AsciiString("WeaponBonusUpgrade"), 132);
    addModuleInternal(&cp167, &dp167, 0, 0, AsciiString("ExperienceScalarUpgrade"), 132);
    addModuleInternal(&cp168, &dp168, 0, 0, AsciiString("MaxHealthUpgrade"), 132);
    addModuleInternal(&cp169, &dp169, 0, 0, AsciiString("ModelConditionUpgrade"), 132);
    addModuleInternal(&cp170, &dp170, 0, 0, AsciiString("AttributeModifierUpgrade"), 132);
    addModuleInternal(&cp171, &dp171, 0, 0, AsciiString("CastleUpgrade"), 132);
    addModuleInternal(&cp172, &dp172, 0, 0, AsciiString("GeometryUpgrade"), 132);
    addModuleInternal(&cp173, &dp173, 0, 0, AsciiString("GarrisonUpgrade"), 132);
    addModuleInternal(&cp174, &dp174, 0, 0, AsciiString("TooltipUpgrade"), 132);
    addModuleInternal(&cp175, &dp175, 0, 0, AsciiString("AudioLoopUpgrade"), 131);
    addModuleInternal(&cp176, &dp176, 0, 0, AsciiString("PassiveAreaEffectBehavior"), 1);
    addModuleInternal(&cp177, &dp177, 0, 0, AsciiString("DominateEnemySpecialPower"), 1);
    addModuleInternal(&cp178, &dp178, 0, 0, AsciiString("TemporarilyDefectUpdate"), 1);
    addModuleInternal(&cp179, &dp179, 0, 0, AsciiString("LockWeaponCreate"), 8);
    addModuleInternal(&cp180, &dp180, 0, 0, AsciiString("PreorderCreate"), 8);
    addModuleInternal(&cp181, &dp181, 0, 0, AsciiString("SupplyCenterCreate"), 8);
    addModuleInternal(&cp182, &dp182, 0, 0, AsciiString("SupplyWarehouseCreate"), 8);
    addModuleInternal(&cp183, &dp183, 0, 0, AsciiString("SpecialPowerCreate"), 8);
    addModuleInternal(&cp184, &dp184, 0, 0, AsciiString("GrantUpgradeCreate"), 8);
    addModuleInternal(&cp185, &dp185, 0, 0, AsciiString("ExperienceLevelCreate"), 8);
    addModuleInternal(&cp186, &dp186, 0, 0, AsciiString("BoneFXDamage"), 4);
    addModuleInternal(&cp187, &dp187, 0, 0, AsciiString("TransitionDamageFX"), 4);
    addModuleInternal(&cp188, &dp188, 0, 0, AsciiString("ReflectDamage"), 4);
    addModuleInternal(&cp189, &dp189, 0, 0, AsciiString("EvacuateDamage"), 4);
    addModuleInternal(&cp190, &dp190, 0, 0, AsciiString("FireWeaponCollide"), 16);
    addModuleInternal(&cp191, &dp191, 0, 0, AsciiString("SquishCollide"), 16);
    addModuleInternal(&cp192, &dp192, 0, 0, AsciiString("AODCrushCollide"), 17);
    addModuleInternal(&cp193, &dp193, 0, 0, AsciiString("HordeMemberCollide"), 16);
    addModuleInternal(&cp194, &dp194, 0, 0, AsciiString("HealCrateCollide"), 16);
    addModuleInternal(&cp195, &dp195, 0, 0, AsciiString("MoneyCrateCollide"), 16);
    addModuleInternal(&cp196, &dp196, 0, 0, AsciiString("ShroudCrateCollide"), 16);
    addModuleInternal(&cp197, &dp197, 0, 0, AsciiString("UnitCrateCollide"), 16);
    addModuleInternal(&cp198, &dp198, 0, 0, AsciiString("VeterancyCrateCollide"), 16);
    addModuleInternal(&cp199, &dp199, 0, 0, AsciiString("SalvageCrateCollide"), 16);
    addModuleInternal(&cp200, &dp200, 0, 0, AsciiString("CivilianSpawnCollide"), 16);
    addModuleInternal(&cp201, &dp201, 0, 0, AsciiString("InactiveBody"), 32);
    addModuleInternal(&cp202, &dp202, 0, 0, AsciiString("ActiveBody"), 32);
    addModuleInternal(&cp203, &dp203, 0, 0, AsciiString("HighlanderBody"), 32);
    addModuleInternal(&cp204, &dp204, 0, 0, AsciiString("ImmortalBody"), 32);
    addModuleInternal(&cp205, &dp205, 0, 0, AsciiString("StructureBody"), 32);
    addModuleInternal(&cp206, &dp206, 0, 0, AsciiString("SymbioticStructuresBody"), 32);
    addModuleInternal(&cp207, &dp207, 0, 0, AsciiString("DelayedDeathBody"), 32);
    addModuleInternal(&cp208, &dp208, 0, 0, AsciiString("FreeLifeBody"), 32);
    addModuleInternal(&cp209, &dp209, 0, 0, AsciiString("DetachableRiderBody"), 32);
    addModuleInternal(&cp210, &dp210, 0, 0, AsciiString("OathbreakerBody"), 32);
    addModuleInternal(&cp211, &dp211, 0, 0, AsciiString("PorcupineFormationBodyModule"), 32);
    addModuleInternal(&cp212, &dp212, 0, 0, AsciiString("RespawnBody"), 32);
    addModuleInternal(&cp213, &dp213, 0, 0, AsciiString("SpecialPowerModule"), 256);
    addModuleInternal(&cp214, &dp214, 0, 0, AsciiString("CashHackSpecialPower"), 256);
    addModuleInternal(&cp215, &dp215, 0, 0, AsciiString("DefectorSpecialPower"), 256);
    addModuleInternal(&cp216, &dp216, 0, 0, AsciiString("LevelGrantSpecialPower"), 1);
    addModuleInternal(&cp217, &dp217, 0, 0, AsciiString("ProductionSpeedBonus"), 256);
    addModuleInternal(&cp218, &dp218, 0, 0, AsciiString("OCLSpecialPower"), 256);
    addModuleInternal(&cp219, &dp219, 0, 0, AsciiString("ElvenWoodSpecialPower"), 256);
    addModuleInternal(&cp220, &dp220, 0, 0, AsciiString("WeaponChangeSpecialPowerModule"), 256);
    addModuleInternal(&cp221, &dp221, 0, 0, AsciiString("ScavengerSpecialPower"), 256);
    addModuleInternal(&cp222, &dp222, 0, 0, AsciiString("CloudBreakSpecialPower"), 256);
    addModuleInternal(&cp223, &dp223, 0, 0, AsciiString("TaintSpecialPower"), 256);
    addModuleInternal(&cp224, &dp224, 0, 0, AsciiString("FreezingRainSpecialPower"), 256);
    addModuleInternal(&cp225, &dp225, 0, 0, AsciiString("DarknessSpecialPower"), 256);
    addModuleInternal(&cp226, &dp226, 0, 0, AsciiString("GrabPassengerSpecialPower"), 256);
    addModuleInternal(&cp227, &dp227, 0, 0, AsciiString("DeflectSpecialPower"), 273);
    addModuleInternal(&cp228, &dp228, 0, 0, AsciiString("SiegeDeploySpecialPower"), 257);
    addModuleInternal(&cp229, &dp229, 0, 0, AsciiString("SiegeDeployHordeSpecialPower"), 257);
    addModuleInternal(&cp230, &dp230, 0, 0, AsciiString("StopSpecialPower"), 256);
    addModuleInternal(&cp231, &dp231, 0, 0, AsciiString("WoundArrowUpdate"), 1);
    addModuleInternal(&cp232, &dp232, 0, 0, AsciiString("FellBeastSwoopPower"), 1);
    addModuleInternal(&cp233, &dp233, 0, 0, AsciiString("ManTheWallsSpecialPower"), 256);
    addModuleInternal(&cp234, &dp234, 0, 0, AsciiString("PlayerUpgradeSpecialPower"), 256);
    addModuleInternal(&cp235, &dp235, 0, 0, AsciiString("PlayerHealSpecialPower"), 256);
    addModuleInternal(&cp236, &dp236, 0, 0, AsciiString("DevastateSpecialPower"), 256);
    addModuleInternal(&cp237, &dp237, 0, 0, AsciiString("SplitHordeSpecialPower"), 256);
    addModuleInternal(&cp238, &dp238, 0, 0, AsciiString("RepairSpecialPower"), 256);
    addModuleInternal(&cp239, &dp239, 0, 0, AsciiString("CombineHordeSpecialPower"), 256);
    addModuleInternal(&cp240, &dp240, 0, 2, AsciiString("AnimatedParticleSysBoneClientUpdate"), 2048);
    addModuleInternal(&cp241, &dp241, 0, 2, AsciiString("SwayClientUpdate"), 2048);
    addModuleInternal(&cp242, &dp242, 0, 2, AsciiString("BeaconClientUpdate"), 2048);
    addModuleInternal(&cp243, &dp243, 0, 3, AsciiString("AnimationSoundClientBehavior"), 4096);
    addModuleInternal(&cp244, &dp244, 0, 3, AsciiString("ModelConditionSoundSelectorClientBehavior"), 4096);
    addModuleInternal(&cp245, &dp245, 0, 3, AsciiString("UpgradeSoundSelectorClientBehavior"), 4096);
    addModuleInternal(&cp246, &dp246, 0, 3, AsciiString("RandomSoundSelectorClientBehavior"), 4096);
}
