-- MySQL dump 10.13  Distrib 8.0.36, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: load_distribution
-- ------------------------------------------------------
-- Server version	5.5.5-10.4.32-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `config`
--

DROP TABLE IF EXISTS `config`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `config` (
  `ConfigYear` year(4) NOT NULL,
  `AnualLoad` int(11) NOT NULL,
  `WeakLoad` int(11) NOT NULL,
  `BadImbalance` tinyint(4) NOT NULL,
  `CriticalImbalance` tinyint(4) NOT NULL,
  PRIMARY KEY (`ConfigYear`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `config`
--

LOCK TABLES `config` WRITE;
/*!40000 ALTER TABLE `config` DISABLE KEYS */;
/*!40000 ALTER TABLE `config` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `department`
--

DROP TABLE IF EXISTS `department`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `department` (
  `DepartmentID` tinyint(4) NOT NULL AUTO_INCREMENT,
  `DepartmentName` varchar(100) NOT NULL,
  PRIMARY KEY (`DepartmentID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `department`
--

LOCK TABLES `department` WRITE;
/*!40000 ALTER TABLE `department` DISABLE KEYS */;
/*!40000 ALTER TABLE `department` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `discipline`
--

DROP TABLE IF EXISTS `discipline`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `discipline` (
  `DisciplineID` int(11) NOT NULL AUTO_INCREMENT,
  `DisciplineName` varchar(100) NOT NULL,
  PRIMARY KEY (`DisciplineID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `discipline`
--

LOCK TABLES `discipline` WRITE;
/*!40000 ALTER TABLE `discipline` DISABLE KEYS */;
/*!40000 ALTER TABLE `discipline` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `disciplineactivity`
--

DROP TABLE IF EXISTS `disciplineactivity`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `disciplineactivity` (
  `DisciplineActivity` int(11) NOT NULL AUTO_INCREMENT,
  `ActivityID` tinyint(4) NOT NULL,
  `DisciplineID` int(11) NOT NULL,
  `StudentGroupID` int(11) DEFAULT NULL,
  `TimePerWeek` decimal(5,3) DEFAULT NULL,
  `GeneralTime` tinyint(4) DEFAULT NULL,
  `DisciplineYear` year(4) NOT NULL,
  `Semester` tinyint(1) DEFAULT NULL,
  `QuantityStudent` smallint(6) DEFAULT NULL,
  PRIMARY KEY (`DisciplineActivity`),
  KEY `ActivityID` (`ActivityID`),
  KEY `StudentGroupID` (`StudentGroupID`),
  KEY `DisciplineID` (`DisciplineID`),
  KEY `fk_da_config` (`DisciplineYear`),
  CONSTRAINT `disciplineactivity_ibfk_1` FOREIGN KEY (`ActivityID`) REFERENCES `typeactivity` (`ActivityID`),
  CONSTRAINT `disciplineactivity_ibfk_3` FOREIGN KEY (`StudentGroupID`) REFERENCES `studentgroup` (`StudentGroupID`),
  CONSTRAINT `disciplineactivity_ibfk_4` FOREIGN KEY (`DisciplineID`) REFERENCES `discipline` (`DisciplineID`),
  CONSTRAINT `fk_da_config` FOREIGN KEY (`DisciplineYear`) REFERENCES `config` (`ConfigYear`) ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `disciplineactivity`
--

LOCK TABLES `disciplineactivity` WRITE;
/*!40000 ALTER TABLE `disciplineactivity` DISABLE KEYS */;
/*!40000 ALTER TABLE `disciplineactivity` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `loadaonyear`
--

DROP TABLE IF EXISTS `loadaonyear`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `loadaonyear` (
  `TeacherID` smallint(6) NOT NULL,
  `AcademicYear` year(4) NOT NULL,
  `TimeOtherLoad` smallint(6) NOT NULL DEFAULT 0,
  `Rate` decimal(4,2) NOT NULL DEFAULT 0.00,
  PRIMARY KEY (`TeacherID`,`AcademicYear`),
  KEY `fk_loadayear_config` (`AcademicYear`),
  CONSTRAINT `fk_loadayear_config` FOREIGN KEY (`AcademicYear`) REFERENCES `config` (`ConfigYear`) ON UPDATE CASCADE,
  CONSTRAINT `loadaonyear_ibfk_1` FOREIGN KEY (`TeacherID`) REFERENCES `teacher` (`TecherID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `loadaonyear`
--

LOCK TABLES `loadaonyear` WRITE;
/*!40000 ALTER TABLE `loadaonyear` DISABLE KEYS */;
/*!40000 ALTER TABLE `loadaonyear` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `post`
--

DROP TABLE IF EXISTS `post`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `post` (
  `PostID` tinyint(4) NOT NULL AUTO_INCREMENT,
  `PostName` varchar(100) NOT NULL,
  PRIMARY KEY (`PostID`)
) ENGINE=InnoDB AUTO_INCREMENT=31 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `post`
--

LOCK TABLES `post` WRITE;
/*!40000 ALTER TABLE `post` DISABLE KEYS */;
INSERT INTO `post` VALUES (1,'Асистент'),(2,'Викладач'),(3,'Старший викладач'),(4,'Доцент'),(5,'Професор'),(6,'Завідувач кафедри'),(7,'Декан'),(8,'Проректор'),(9,'Ректор');
/*!40000 ALTER TABLE `post` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `quantitystudentongroup`
--

DROP TABLE IF EXISTS `quantitystudentongroup`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `quantitystudentongroup` (
  `StudentGroupID` int(11) NOT NULL,
  `SettingsYear` year(4) NOT NULL,
  `QuantityStudent` smallint(6) NOT NULL,
  PRIMARY KEY (`StudentGroupID`,`SettingsYear`),
  KEY `fk_qsg_config` (`SettingsYear`),
  CONSTRAINT `fk_qsg_config` FOREIGN KEY (`SettingsYear`) REFERENCES `config` (`ConfigYear`) ON UPDATE CASCADE,
  CONSTRAINT `quantitystudentongroup_ibfk_1` FOREIGN KEY (`StudentGroupID`) REFERENCES `studentgroup` (`StudentGroupID`) ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `quantitystudentongroup`
--

LOCK TABLES `quantitystudentongroup` WRITE;
/*!40000 ALTER TABLE `quantitystudentongroup` DISABLE KEYS */;
/*!40000 ALTER TABLE `quantitystudentongroup` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `speciality`
--

DROP TABLE IF EXISTS `speciality`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `speciality` (
  `SpecialityNumber` smallint(6) NOT NULL,
  `DepartmentID` tinyint(4) NOT NULL,
  `SpecialityName` varchar(100) NOT NULL,
  PRIMARY KEY (`SpecialityNumber`),
  KEY `DepartmentID` (`DepartmentID`),
  CONSTRAINT `speciality_ibfk_1` FOREIGN KEY (`DepartmentID`) REFERENCES `department` (`DepartmentID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `speciality`
--

LOCK TABLES `speciality` WRITE;
/*!40000 ALTER TABLE `speciality` DISABLE KEYS */;
/*!40000 ALTER TABLE `speciality` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `studentgroup`
--

DROP TABLE IF EXISTS `studentgroup`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `studentgroup` (
  `StudentGroupID` int(11) NOT NULL AUTO_INCREMENT,
  `SpecialityNumber` smallint(6) NOT NULL,
  `GroupYear` year(4) NOT NULL,
  `GroupNumber` tinyint(4) NOT NULL DEFAULT 1,
  PRIMARY KEY (`StudentGroupID`),
  KEY `SpecialityNumber` (`SpecialityNumber`),
  CONSTRAINT `studentgroup_ibfk_1` FOREIGN KEY (`SpecialityNumber`) REFERENCES `speciality` (`SpecialityNumber`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `studentgroup`
--

LOCK TABLES `studentgroup` WRITE;
/*!40000 ALTER TABLE `studentgroup` DISABLE KEYS */;
/*!40000 ALTER TABLE `studentgroup` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `teacher`
--

DROP TABLE IF EXISTS `teacher`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `teacher` (
  `TecherID` smallint(6) NOT NULL AUTO_INCREMENT,
  `FName` varchar(100) NOT NULL,
  `SName` varchar(100) NOT NULL,
  `LName` varchar(100) DEFAULT NULL,
  `PostID` tinyint(4) NOT NULL,
  PRIMARY KEY (`TecherID`),
  KEY `PostID` (`PostID`),
  CONSTRAINT `teacher_ibfk_1` FOREIGN KEY (`PostID`) REFERENCES `post` (`PostID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `teacher`
--

LOCK TABLES `teacher` WRITE;
/*!40000 ALTER TABLE `teacher` DISABLE KEYS */;
/*!40000 ALTER TABLE `teacher` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `teachingload`
--

DROP TABLE IF EXISTS `teachingload`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `teachingload` (
  `DisciplineActivityID` int(11) NOT NULL,
  `TecherID` smallint(6) NOT NULL,
  PRIMARY KEY (`DisciplineActivityID`,`TecherID`),
  UNIQUE KEY `DisciplineActivityID` (`DisciplineActivityID`),
  KEY `TecherID` (`TecherID`),
  CONSTRAINT `teachingload_ibfk_1` FOREIGN KEY (`DisciplineActivityID`) REFERENCES `disciplineactivity` (`DisciplineActivity`),
  CONSTRAINT `teachingload_ibfk_2` FOREIGN KEY (`TecherID`) REFERENCES `teacher` (`TecherID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `teachingload`
--

LOCK TABLES `teachingload` WRITE;
/*!40000 ALTER TABLE `teachingload` DISABLE KEYS */;
/*!40000 ALTER TABLE `teachingload` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `typeactivity`
--

DROP TABLE IF EXISTS `typeactivity`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `typeactivity` (
  `ActivityID` tinyint(4) NOT NULL AUTO_INCREMENT,
  `ActivityName` varchar(100) NOT NULL,
  `IsGroupLoad` tinyint(1) NOT NULL DEFAULT 1,
  PRIMARY KEY (`ActivityID`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `typeactivity`
--

LOCK TABLES `typeactivity` WRITE;
/*!40000 ALTER TABLE `typeactivity` DISABLE KEYS */;
INSERT INTO `typeactivity` VALUES (1,'Лекція',0),(2,'Лабораторна робота',0),(3,'Практичне заняття',1),(4,'Екзамен',0),(5,'Курсова робота',0);
/*!40000 ALTER TABLE `typeactivity` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2026-05-15 17:05:58
