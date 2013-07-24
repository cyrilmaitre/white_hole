-- phpMyAdmin SQL Dump
-- version 3.3.9
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Nov 07, 2012 at 11:51 PM
-- Server version: 5.1.53
-- PHP Version: 5.3.4

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `spaceumad`
--

-- --------------------------------------------------------

--
-- Table structure for table `spaceumad_ammo`
--

CREATE TABLE IF NOT EXISTS `spaceumad_ammo` (
  `mIdAmmo` int(11) NOT NULL AUTO_INCREMENT,
  `mDescription` varchar(255) DEFAULT NULL,
  `mName` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`mIdAmmo`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Dumping data for table `spaceumad_ammo`
--

INSERT INTO `spaceumad_ammo` (`mIdAmmo`, `mDescription`, `mName`) VALUES
(0, 'ammo200mmDescription', 'ammo200mmName'),
(1, 'ammo200mmAntiShieldDescription', 'ammo200mmAntiShieldName');

-- --------------------------------------------------------

--
-- Table structure for table `spaceumad_ammotype`
--

CREATE TABLE IF NOT EXISTS `spaceumad_ammotype` (
  `mIdAmmoType` int(11) NOT NULL AUTO_INCREMENT,
  `mDescription` varchar(255) DEFAULT NULL,
  `mName` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`mIdAmmoType`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=4 ;

--
-- Dumping data for table `spaceumad_ammotype`
--

INSERT INTO `spaceumad_ammotype` (`mIdAmmoType`, `mDescription`, `mName`) VALUES
(0, 'ammoTypeNormalDescription', 'ammoTypeNormalName'),
(1, 'ammoTypeAntiShieldDescription', 'ammoTypeAntiShieldName'),
(2, 'ammoTypeAntiArmorDescription', 'ammoTypeAntiArmorName'),
(3, 'ammoTypeAntiStructureDescription', 'ammoTypeAntiStructureName');

-- --------------------------------------------------------

--
-- Table structure for table `spaceumad_character`
--

CREATE TABLE IF NOT EXISTS `spaceumad_character` (
  `mIdCharacter` int(11) NOT NULL AUTO_INCREMENT,
  `mAlive` bit(1) NOT NULL,
  `mAvatarId` varchar(255) DEFAULT NULL,
  `mDateCreation` datetime DEFAULT NULL,
  `mExperience` int(11) NOT NULL,
  `mLevel` int(11) NOT NULL,
  `mName` varchar(255) DEFAULT NULL,
  `mSkillPoints` int(11) NOT NULL,
  `mTimePlayed` bigint(20) NOT NULL,
  `mIdJob` int(11) DEFAULT NULL,
  `mIdRace` int(11) DEFAULT NULL,
  `mIdUser` int(11) DEFAULT NULL,
  PRIMARY KEY (`mIdCharacter`),
  KEY `FK82FCCB2BF8A36B6B` (`mIdUser`),
  KEY `FK82FCCB2BF8A02977` (`mIdRace`),
  KEY `FK82FCCB2B39915505` (`mIdJob`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

--
-- Dumping data for table `spaceumad_character`
--


-- --------------------------------------------------------

--
-- Table structure for table `spaceumad_character_ship`
--

CREATE TABLE IF NOT EXISTS `spaceumad_character_ship` (
  `mIdCharacterShip` int(11) NOT NULL AUTO_INCREMENT,
  `mExperience` int(11) NOT NULL,
  `mLevel` int(11) NOT NULL,
  `mIdShipModel` int(11) DEFAULT NULL,
  `mIdCharacter` int(11) DEFAULT NULL,
  `mPiloted` bit(1) NOT NULL,
  PRIMARY KEY (`mIdCharacterShip`),
  KEY `FKB11B0AD0C77AB34D` (`mIdShipModel`),
  KEY `FKB11B0AD043426B58` (`mIdCharacter`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

--
-- Dumping data for table `spaceumad_character_ship`
--


-- --------------------------------------------------------

--
-- Table structure for table `spaceumad_character_skill`
--

CREATE TABLE IF NOT EXISTS `spaceumad_character_skill` (
  `mIdCharacterSkill` int(11) NOT NULL AUTO_INCREMENT,
  `mLevel` int(11) NOT NULL,
  `mIdCharacter` int(11) DEFAULT NULL,
  `mIdSkill` int(11) DEFAULT NULL,
  PRIMARY KEY (`mIdCharacterSkill`),
  KEY `FK7247AC3DDF3DFF9D` (`mIdCharacter`),
  KEY `FK7247AC3D1B8A7B6D` (`mIdSkill`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

--
-- Dumping data for table `spaceumad_character_skill`
--


-- --------------------------------------------------------

--
-- Table structure for table `spaceumad_job`
--

CREATE TABLE IF NOT EXISTS `spaceumad_job` (
  `mIdJob` int(11) NOT NULL AUTO_INCREMENT,
  `mDescription` varchar(255) DEFAULT NULL,
  `mName` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`mIdJob`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=4 ;

--
-- Dumping data for table `spaceumad_job`
--

INSERT INTO `spaceumad_job` (`mIdJob`, `mDescription`, `mName`) VALUES
(0, 'jobMercenaryDescription', 'jobMercenaryName'),
(1, 'jobIndustrialistDescription', 'jobIndustrialistName'),
(2, 'jobTraderDescription', 'jobTraderName'),
(3, 'jobBuilderDescription', 'jobBuilderName');

-- --------------------------------------------------------

--
-- Table structure for table `spaceumad_race`
--

CREATE TABLE IF NOT EXISTS `spaceumad_race` (
  `mIdRace` int(11) NOT NULL AUTO_INCREMENT,
  `mDescription` varchar(255) DEFAULT NULL,
  `mName` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`mIdRace`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Dumping data for table `spaceumad_race`
--

INSERT INTO `spaceumad_race` (`mIdRace`, `mDescription`, `mName`) VALUES
(0, 'raceHumanDescription', 'raceHumanName'),
(1, 'raceAndroidDescription', 'raceAndroidName');

-- --------------------------------------------------------

--
-- Table structure for table `spaceumad_ship_model`
--

CREATE TABLE IF NOT EXISTS `spaceumad_ship_model` (
  `mIdShipModel` int(11) NOT NULL AUTO_INCREMENT,
  `mDescription` varchar(255) DEFAULT NULL,
  `mName` varchar(255) DEFAULT NULL,
  `mIdShipType` int(11) DEFAULT NULL,
  PRIMARY KEY (`mIdShipModel`),
  KEY `FKF3918BA4B3E15619` (`mIdShipType`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

--
-- Dumping data for table `spaceumad_ship_model`
--

INSERT INTO `spaceumad_ship_model` (`mIdShipModel`, `mDescription`, `mName`, `mIdShipType`) VALUES
(0, 'shipModelFXT01Description', 'shipModelFXT01Name', 8),
(1, 'shipModelFXT02Description', 'shipModelFXT02Name', 8),
(2, 'shipModelFXT03Description', 'shipModelFXT03Name', 8);

-- --------------------------------------------------------

--
-- Table structure for table `spaceumad_ship_type`
--

CREATE TABLE IF NOT EXISTS `spaceumad_ship_type` (
  `mIdShipType` int(11) NOT NULL AUTO_INCREMENT,
  `mDescription` varchar(255) DEFAULT NULL,
  `mName` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`mIdShipType`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=11 ;

--
-- Dumping data for table `spaceumad_ship_type`
--

INSERT INTO `spaceumad_ship_type` (`mIdShipType`, `mDescription`, `mName`) VALUES
(0, 'shipTypeBattleDescription', 'shipTypeBattleName'),
(1, 'shipTypeBattlecruiserDescription', 'shipTypeBattlecruiserName'),
(2, 'shipTypeBattleshipDescription', 'shipTypeBattleshipName'),
(3, 'shipTypeCarrierDescription', 'shipTypeCarrierName'),
(4, 'shipTypeCruiserDescription', 'shipTypeCruiserName'),
(5, 'shipTypeDestroyerDescription', 'shipTypeDestroyerName'),
(6, 'shipTypeDreadnoughtDescription', 'shipTypeDreadnoughtName'),
(7, 'shipTypeFighterDescription', 'shipTypeFighterName'),
(8, 'shipTypeFrigateDescription', 'shipTypeFrigateName'),
(9, 'shipTypeScoutDescription', 'shipTypeScoutName'),
(10, 'shipTypeTransportDescription', 'shipTypeTransportName');

-- --------------------------------------------------------

--
-- Table structure for table `spaceumad_skill`
--

CREATE TABLE IF NOT EXISTS `spaceumad_skill` (
  `mIdSkill` int(11) NOT NULL AUTO_INCREMENT,
  `mDescription` varchar(255) DEFAULT NULL,
  `mName` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`mIdSkill`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=9 ;

--
-- Dumping data for table `spaceumad_skill`
--

INSERT INTO `spaceumad_skill` (`mIdSkill`, `mDescription`, `mName`) VALUES
(0, 'skillFightingDescription', 'skillFightingName'),
(1, 'skillDroneDescription', 'skillDroneName'),
(2, 'skillSteeringDescription', 'skillSteeringName'),
(3, 'skillMiningDescription', 'skillMiningName'),
(4, 'skillCraftingDescription', 'skillCraftingName'),
(5, 'skillAlchemyDescription', 'skillAlchemyName'),
(6, 'skillBargainingDescription', 'skillBargainingName'),
(7, 'skillSalvagingDescription', 'skillSalvagingName'),
(8, 'skillConstructionDescription', 'skillConstructionName');

-- --------------------------------------------------------

--
-- Table structure for table `spaceumad_user`
--

CREATE TABLE IF NOT EXISTS `spaceumad_user` (
  `mIdUser` int(11) NOT NULL AUTO_INCREMENT,
  `mAdmin` bit(1) NOT NULL,
  `mEmail` varchar(255) DEFAULT NULL,
  `mPassword` varchar(255) DEFAULT NULL,
  `mRegisterDate` datetime DEFAULT NULL,
  `mUsername` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`mIdUser`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Dumping data for table `spaceumad_user`
--

INSERT INTO `spaceumad_user` (`mIdUser`, `mAdmin`, `mEmail`, `mPassword`, `mRegisterDate`, `mUsername`) VALUES
(1, b'0', '92807@supinfo.com', 'c4278fa5c38518cf32b5799c9e66ed456908a31c', '2012-10-25 02:30:08', 'ikg');

-- --------------------------------------------------------

--
-- Table structure for table `spaceumad_weapon`
--

CREATE TABLE IF NOT EXISTS `spaceumad_weapon` (
  `mIdWeapon` int(11) NOT NULL AUTO_INCREMENT,
  `mActif` bit(1) NOT NULL,
  `mAmmoCount` int(11) NOT NULL,
  `mIdAmmo` int(11) DEFAULT NULL,
  `mIdCharacterShip` int(11) DEFAULT NULL,
  `mIdWeaponModel` int(11) DEFAULT NULL,
  PRIMARY KEY (`mIdWeapon`),
  KEY `FKC33C815A93D5B36D` (`mIdWeaponModel`),
  KEY `FKC33C815A8E74FAFD` (`mIdCharacterShip`),
  KEY `FKC33C815ACE1C3A89` (`mIdAmmo`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

--
-- Dumping data for table `spaceumad_weapon`
--


-- --------------------------------------------------------

--
-- Table structure for table `spaceumad_weaponmodel`
--

CREATE TABLE IF NOT EXISTS `spaceumad_weaponmodel` (
  `mIdWeaponModel` int(11) NOT NULL AUTO_INCREMENT,
  `mDescription` varchar(255) DEFAULT NULL,
  `mName` varchar(255) DEFAULT NULL,
  `mIdWeaponType` int(11) DEFAULT NULL,
  PRIMARY KEY (`mIdWeaponModel`),
  KEY `FKA334420F2E15D1F9` (`mIdWeaponType`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

--
-- Dumping data for table `spaceumad_weaponmodel`
--

INSERT INTO `spaceumad_weaponmodel` (`mIdWeaponModel`, `mDescription`, `mName`, `mIdWeaponType`) VALUES
(0, 'weaponModelMediumAutoCannonDescription', 'weaponModelMediumAutoCannonName', 0),
(1, 'weaponModelMediumAutoCannonDescription', 'weaponModelMediumAutoCannonName', 0),
(2, 'weaponModelLargeAutoCannonDescription', 'weaponModelLargeAutoCannonName', 0);

-- --------------------------------------------------------

--
-- Table structure for table `spaceumad_weapontype`
--

CREATE TABLE IF NOT EXISTS `spaceumad_weapontype` (
  `mIdWeaponType` int(11) NOT NULL AUTO_INCREMENT,
  `mDescription` varchar(255) DEFAULT NULL,
  `mName` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`mIdWeaponType`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

--
-- Dumping data for table `spaceumad_weapontype`
--

INSERT INTO `spaceumad_weapontype` (`mIdWeaponType`, `mDescription`, `mName`) VALUES
(0, 'weaponTypeKineticDescription', 'weaponTypeKineticName'),
(1, 'weaponTypeLaserDescription', 'weaponTypeLaserName'),
(2, 'weaponTypeMissileLauncherDescription', 'weaponTypeMissileLauncherName');
