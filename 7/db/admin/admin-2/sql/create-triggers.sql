USE `mydb`;
CREATE DEFINER = CURRENT_USER TRIGGER `mydb`.`trips_BEFORE_INSERT` BEFORE INSERT ON `trips` FOR EACH ROW
BEGIN

    DECLARE tourist_level INT;
    DECLARE tour_level INT;

	IF NEW.started = 1
	THEN
	  SIGNAL  SQLSTATE '45000'
		SET MESSAGE_TEXT = 'Cannot start at the moment of creation';
	END IF;

    IF NEW.completed = 1 THEN
      SIGNAL  SQLSTATE '45000'
		SET MESSAGE_TEXT = 'Cannot finish at the moment of creation';
    END IF;

     SET tourist_level = (SELECT level FROM tourists WHERE id = NEW.leader_id);
     SET tour_level = (SELECT level FROM tours WHERE id = NEW.tours_id);

     IF tourist_level < 2 AND tourist_level < tour_level THEN
        SET @message = concat('Leaders`s level should be greater than tour level, tour_level: ', tour_level,  ', leader_level: ', tourist_level);
	 SIGNAL  SQLSTATE '45000'
        SET MESSAGE_TEXT = @message;
	 END IF;

END;

USE `mydb`;
CREATE DEFINER = CURRENT_USER TRIGGER `mydb`.`trips_BEFORE_UPDATE` BEFORE UPDATE ON `trips` FOR EACH ROW
BEGIN
    DECLARE tourist_level INT;
    DECLARE tour_level INT;

	IF NEW.started > 0 AND (SELECT COUNT(*) FROM `mydb`.`trips_tourists` WHERE trips_id = NEW.id) < 4
	THEN
	  SIGNAL  SQLSTATE '45000'
		SET MESSAGE_TEXT = 'Trip mush have 5+ participants';
	END IF;
    IF NEW.completed > 0 AND OLD.started = 0 THEN
      SIGNAL  SQLSTATE '45000'
		SET MESSAGE_TEXT = 'Cannot finish until started';
    END IF;

     SET tourist_level = (SELECT level FROM tourists WHERE id = NEW.leader_id);
     SET tour_level = (SELECT level FROM tours WHERE id = NEW.tours_id);

     IF tourist_level < 2 AND tourist_level < tour_level THEN
        SET @message = concat('Leaders`s level should gte than tour level, tour_level: ', tour_level,  ', leader_level: ', tourist_level);
	 SIGNAL  SQLSTATE '45000'
        SET MESSAGE_TEXT = @message;
	 END IF;
END;

USE `mydb`;
CREATE DEFINER = CURRENT_USER TRIGGER `mydb`.`trips_tourists_BEFORE_INSERT` BEFORE INSERT ON `trips_tourists` FOR EACH ROW
BEGIN
	DECLARE tourist_level INT;
    DECLARE tour_level INT;
    DECLARE tour_id INT;

    SET tourist_level = (SELECT level FROM tourists WHERE id = NEW.tourists_id);
    SET tour_id = (SELECT tours_id FROM trips WHERE id = NEW.trips_id);
    SET tour_level = (SELECT level FROM tours WHERE id = tour_id);

    IF tourist_level < tour_level THEN
        SET @message = concat('Tourist`s level should gte than tour level, tour_level: ', tour_level,  ', tourist_level: ', tourist_level);
      SIGNAL  SQLSTATE '45000'
        SET MESSAGE_TEXT = @message;
    END IF;
END;
