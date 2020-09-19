/*
Navicat MySQL Data Transfer

Source Server         : localhost
Source Server Version : 80018
Source Host           : localhost:3306
Source Database       : shoppingmall

Target Server Type    : MYSQL
Target Server Version : 80018
File Encoding         : 65001

Date: 2020-01-03 14:35:01
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for cart
-- ----------------------------
DROP TABLE IF EXISTS `cart`;
CREATE TABLE `cart` (
  `user_id` int(255) NOT NULL,
  `thing_id` int(255) NOT NULL,
  `thing_name` varchar(255) NOT NULL,
  `num` int(2) NOT NULL,
  PRIMARY KEY (`user_id`,`thing_id`),
  KEY `thing_id` (`thing_id`),
  CONSTRAINT `thing_id` FOREIGN KEY (`thing_id`) REFERENCES `thing` (`thing_id`),
  CONSTRAINT `user_id` FOREIGN KEY (`user_id`) REFERENCES `user` (`user_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of cart
-- ----------------------------
INSERT INTO `cart` VALUES ('111', '1', '手机', '9');
INSERT INTO `cart` VALUES ('111', '2', '电脑', '2');
INSERT INTO `cart` VALUES ('111', '3', '眼镜', '1');
INSERT INTO `cart` VALUES ('111', '4', '手表', '1');
INSERT INTO `cart` VALUES ('444', '1', '手机', '1');
INSERT INTO `cart` VALUES ('444', '2', '电脑', '1');
INSERT INTO `cart` VALUES ('444', '3', '眼镜', '1');
INSERT INTO `cart` VALUES ('555', '1', '手机', '1');
INSERT INTO `cart` VALUES ('555', '2', '电脑', '1');
INSERT INTO `cart` VALUES ('555', '3', '眼镜', '1');
INSERT INTO `cart` VALUES ('555', '4', '手表', '1');
INSERT INTO `cart` VALUES ('666', '1', '手机', '2');

-- ----------------------------
-- Table structure for producer
-- ----------------------------
DROP TABLE IF EXISTS `producer`;
CREATE TABLE `producer` (
  `producer_id` int(255) NOT NULL,
  `producer_name` varchar(255) NOT NULL,
  `password` varchar(6) NOT NULL,
  PRIMARY KEY (`producer_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of producer
-- ----------------------------
INSERT INTO `producer` VALUES ('1111', 'cccc', '1111');

-- ----------------------------
-- Table structure for thing
-- ----------------------------
DROP TABLE IF EXISTS `thing`;
CREATE TABLE `thing` (
  `thing_id` int(255) NOT NULL,
  `thing_name` varchar(255) NOT NULL,
  `price` decimal(10,2) NOT NULL,
  `num` int(2) NOT NULL,
  `producer_id` int(255) NOT NULL,
  PRIMARY KEY (`thing_id`,`producer_id`),
  KEY `thing_id` (`thing_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of thing
-- ----------------------------
INSERT INTO `thing` VALUES ('1', '手机', '1000.00', '35', '1111');
INSERT INTO `thing` VALUES ('2', '电脑', '3000.00', '85', '1111');
INSERT INTO `thing` VALUES ('3', '眼镜', '50.00', '993', '1111');
INSERT INTO `thing` VALUES ('4', '手表', '309.00', '71', '1111');

-- ----------------------------
-- Table structure for user
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `user_id` int(255) NOT NULL,
  `user_name` varchar(255) NOT NULL,
  `sex` int(1) NOT NULL,
  `password` varchar(255) NOT NULL,
  PRIMARY KEY (`user_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of user
-- ----------------------------
INSERT INTO `user` VALUES ('111', 'xiha', '1', '111');
INSERT INTO `user` VALUES ('222', 'hahaha', '0', '222');
INSERT INTO `user` VALUES ('333', 'youqian', '1', '333');
INSERT INTO `user` VALUES ('444', 'xixixixi', '0', '444');
INSERT INTO `user` VALUES ('555', 'hihihila', '0', '555');
INSERT INTO `user` VALUES ('666', 'la', '0', '666');
DROP TRIGGER IF EXISTS `thing_in`;
DELIMITER ;;
CREATE TRIGGER `thing_in` BEFORE INSERT ON `thing` FOR EACH ROW BEGIN
    DECLARE msg VARCHAR (255); 
    IF NEW.num<0 then 
    set msg = "数量不能小于0";
    SIGNAL SQLSTATE 'HY000' SET mysql_errno = 22, message_text = msg;
    END IF;    
END
;;
DELIMITER ;
DROP TRIGGER IF EXISTS `price_in`;
DELIMITER ;;
CREATE TRIGGER `price_in` BEFORE INSERT ON `thing` FOR EACH ROW BEGIN
    DECLARE msg VARCHAR (255); 
    IF NEW.price<0 then 
    set msg = "价格不能小于0";
    SIGNAL SQLSTATE 'HY000' SET mysql_errno = 22, message_text = msg;
    END IF;    
END
;;
DELIMITER ;
DROP TRIGGER IF EXISTS `thing_up`;
DELIMITER ;;
CREATE TRIGGER `thing_up` BEFORE UPDATE ON `thing` FOR EACH ROW BEGIN
    DECLARE msg VARCHAR (255); 
    IF NEW.num<0 then 
    set msg = "数量不能小于0";
    SIGNAL SQLSTATE 'HY000' SET mysql_errno = 22, message_text = msg;
    END IF;    
END
;;
DELIMITER ;
DROP TRIGGER IF EXISTS `price_up`;
DELIMITER ;;
CREATE TRIGGER `price_up` BEFORE UPDATE ON `thing` FOR EACH ROW BEGIN
    DECLARE msg VARCHAR (255); 
    IF NEW.price<0 then 
    set msg = "价格不能小于0";
    SIGNAL SQLSTATE 'HY000' SET mysql_errno = 22, message_text = msg;
    END IF;    
END
;;
DELIMITER ;
