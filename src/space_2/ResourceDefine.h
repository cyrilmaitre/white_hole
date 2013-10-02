#ifndef RESOURCE_DEFINE_
#define RESOURCE_DEFINE_

// Window Properties
#define APP_SCREEN_COLOR				32
#define APP_GAME_NAME					"White Hole"

// Images
#define FOLDER_IMAGE						"image/"
#define FOLDER_IMAGE_BOOT					FOLDER_IMAGE"boot/"
#define FOLDER_IMAGE_SPACE					FOLDER_IMAGE"space/"
#define FOLDER_IMAGE_SPACE_SHIP				FOLDER_IMAGE_SPACE"ship/"
#define FOLDER_IMAGE_SPACE_CLOUDGAZ			FOLDER_IMAGE_SPACE"cloud_gaz/"
#define FOLDER_IMAGE_SPACE_CLOUDWRECK		FOLDER_IMAGE_SPACE"cloud_wreck/"
#define FOLDER_IMAGE_SPACE_SHIP				FOLDER_IMAGE_SPACE"ship/"
#define FOLDER_IMAGE_SPACE_PLANET			FOLDER_IMAGE_SPACE"planet/"
#define FOLDER_IMAGE_SPACE_TURRET			FOLDER_IMAGE_SPACE"turret/"
#define FOLDER_IMAGE_SPACE_STAR				FOLDER_IMAGE_SPACE"star/"
#define FOLDER_IMAGE_SPACE_WRECK			FOLDER_IMAGE_SPACE"wreck/"
#define FOLDER_IMAGE_SPACE_STATION			FOLDER_IMAGE_SPACE"station/"
#define FOLDER_IMAGE_SPACE_PROJECTILE		FOLDER_IMAGE_SPACE"projectile/"
#define FOLDER_IMAGE_UIGAME					FOLDER_IMAGE"uigame/"
#define FOLDER_IMAGE_UIGAME_WINDOW			FOLDER_IMAGE_UIGAME"window/"
#define FOLDER_IMAGE_UIGAME_SCREENSTATION	FOLDER_IMAGE_UIGAME"station_background/"
#define FOLDER_IMAGE_MISC					FOLDER_IMAGE"misc/"

#define IMG_BOOT_SCREEN						"boot_screen.png"
#define IMG_WINDOW_TOPLEFT					"window_topLeft.png"
#define IMG_WINDOW_TOP						"window_top.png"
#define IMG_WINDOW_TOPRIGHT					"window_topRight.png"
#define IMG_WINDOW_LEFT						"window_left.png"
#define IMG_WINDOW_BACKGROUND				"window_center.png"
#define IMG_WINDOW_RIGHT					"window_right.png"
#define IMG_WINDOW_BOTTOM					"window_bottom.png"
#define IMG_WINDOW_ACTIONBARBUTTON			"window_buttons.png"
#define IMG_ICON10X10						"icon_10x10.png"
#define IMG_ICON16X16						"icon_16x16.png"
#define IMG_ICON32X32						"icon_32x32.png"
#define IMG_ICON48X48						"icon_48x48.png"
#define IMG_ICON64X64						"icon_64x64.png"
#define IMG_SPACE_BACKGROUND				"space_background.png"
#define IMG_LOADING_SQUARE_CIRCLE			"loading_squares_circle.png"
#define IMG_SCROLLBAR						"scrollbar.png"
#define IMG_RACE							"race.png"
#define IMG_AVATAR							"avatar.png"
#define IMG_JOB								"job.png"
#define IMG_SKILL							"skill.png"
#define IMG_POPUP_BUBBLE_ARROW				"popup-bubble-arrow.png"
#define IMG_ITEMS							"items.png"
#define IMG_ITEMTYPES						"itemtypes.png"
#define IMG_INTERFACE_BOTTOM				"interface_bottom.png"
#define IMG_IMPACT_BULLET					"impact_bullet.png"
#define IMG_IMPACT_LASER					"impact_laser.png"
#define IMG_IMPACT_EXPLOSION				"impact_explosion.png"
#define IMG_PROJECTILE_BULLET				"projectile_bullet.png"
#define IMG_PROJECTILE_LASER				"projectile_laser.png"
#define IMG_PROJECTILE_LASER_GLOW			"projectile_laser_glow.png"
#define IMG_PROJECTILE_LASERBALL			"projectile_laserball.png"
#define IMG_PROJECTILE_LASERBALL_GLOW		"projectile_laserball_glow.png"
#define IMG_PROJECTILE_MISSILE				"projectile_missile.png"
#define IMG_PROJECTILE_MISSILE_GLOW			"projectile_missile_glow.png"
#define IMG_PROJECTILE_ROCKET				"projectile_rocket.png"
#define IMG_PROJECTILE_ROCKET_GLOW			"projectile_rocket_glow.png"

// Fonts
#define FOLDER_FONT					"font/"
#define FONT_MKS_KONTRAPUNKT		"mks_kontrapunkt.ttf"
#define FONT_MKS_UNIBODY			"mks_unibody.ttf"
#define FONT_DEFAULT				FONT_MKS_KONTRAPUNKT
#define FONT_UI						FONT_MKS_KONTRAPUNKT
#define FONT_UITHEME				FONT_MKS_UNIBODY

// Sound
#define FOLDER_SOUND					"sound/"
#define SOUND_SHIPJET					"ship_jet.wav"
#define SOUND_OBJECTDESTRUCTION			"object_destruction.wav"
#define SOUND_WEAPON_KINETIC_1			"weapon_kinetic_1.wav"
#define SOUND_WEAPON_KINETIC_2			"weapon_kinetic_2.wav"
#define SOUND_WEAPON_KINETIC_RELOAD		"weapon_kinetic_reload.wav"

// Music
#define FOLDER_MUSIC					"sound/music/"

#define MUSIC_THEME_1					"theme_1.wav"
#define MUSIC_THEME_2					"theme_2.wav"
#define MUSIC_THEME_3					"theme_3.wav"
#define MUSIC_THEME_4					"theme_4.wav"				
#define THEME_1_NAME					"Theme number 1"
#define THEME_2_NAME					"Theme number 2"
#define THEME_3_NAME					"Theme number 3"
#define THEME_4_NAME					"Theme number 4"

// Config
#define FOLDER_CONFIG							"config/"
#define FOLDER_CONFIG_ITEMTIER					FOLDER_CONFIG"itemtier/"
#define FOLDER_CONFIG_ITEMTYPE					FOLDER_CONFIG"itemtype/"
#define FOLDER_CONFIG_SHIPMODEL					FOLDER_CONFIG"shipmodel/"
#define FOLDER_CONFIG_GENERAL					FOLDER_CONFIG"general/"
#define FOLDER_CONFIG_GENERAL_DANGERLEVEL		FOLDER_CONFIG_GENERAL"dangerlevel/"
#define FOLDER_CONFIG_GENERAL_CHARACTERLEVEL	FOLDER_CONFIG_GENERAL"characterlevel/"
#define FOLDER_CONFIG_GENERAL_SHIPLEVEL			FOLDER_CONFIG_GENERAL"shiplevel/"
#define FOLDER_CONFIG_RACE						FOLDER_CONFIG"race/"
#define FOLDER_CONFIG_JOB						FOLDER_CONFIG"job/"
#define FOLDER_CONFIG_SKILL						FOLDER_CONFIG"skill/"
#define FOLDER_CONFIG_AMMOTYPE					FOLDER_CONFIG"ammotype/"
#define FOLDER_CONFIG_AMMO						FOLDER_CONFIG"ammomodel/"
#define FOLDER_CONFIG_WEAPONTYPE				FOLDER_CONFIG"weapontype/"
#define FOLDER_CONFIG_WEAPONMODEL				FOLDER_CONFIG"weaponmodel/"
#define FOLDER_CONFIG_NPCTYPE					FOLDER_CONFIG"npctype/"
#define FOLDER_CONFIG_NPCSHIPMODEL				FOLDER_CONFIG"npcshipmodel/"
#define FOLDER_CONFIG_ITEM						FOLDER_CONFIG"item/"
#define FOLDER_CONFIG_PLANETMODEL				FOLDER_CONFIG"planetmodel/"
#define FOLDER_CONFIG_PLANETTYPE				FOLDER_CONFIG"planettype/"
#define FOLDER_CONFIG_CLOUDGAZMODEL				FOLDER_CONFIG"cloudgazmodel/"
#define FOLDER_CONFIG_CLOUDWRECKMODEL			FOLDER_CONFIG"cloudwreckmodel/"
#define FOLDER_CONFIG_LOOTITEMMODEL				FOLDER_CONFIG"lootitemmodel/"
#define FOLDER_CONFIG_STATIONMODEL				FOLDER_CONFIG"stationmodel/"
#define FOLDER_CONFIG_STARMODEL					FOLDER_CONFIG"starmodel/"
#define FOLDER_CONFIG_TURRETEFFECTMODEL			FOLDER_CONFIG"turreteffectmodel/"

// Usefull
#define CARDINALITY_NORTH				0
#define CARDINALITY_NORTHEAST			1
#define CARDINALITY_EAST				2
#define CARDINALITY_SOUTHEAST			3
#define CARDINALITY_SOUTH				4
#define CARDINALITY_SOUTHWEST			5
#define CARDINALITY_WEST				6
#define CARDINALITY_NORTHWEST			7

#endif