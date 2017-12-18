-- + 5+ participants in a trip
-- + participants level >= tour level (initial value for level = 0)
-- + leader_level == 2 OR (leader_level > tour_level)
-- - when trip completed participant_level = max(participant_level, tour_level)
-- + do not finish until started

INSERT INTO `tours` (`id`, `name`, `level`) VALUES (1, LEFT(UUID(), 8), 0);
INSERT INTO `tours` (`id`, `name`, `level`) VALUES (2, LEFT(UUID(), 8), 0);
INSERT INTO `tours` (`id`, `name`, `level`) VALUES (3, LEFT(UUID(), 8), 0);
INSERT INTO `tours` (`id`, `name`, `level`) VALUES (4, LEFT(UUID(), 8), 0);
INSERT INTO `tours` (`id`, `name`, `level`) VALUES (5, LEFT(UUID(), 8), 1);
INSERT INTO `tours` (`id`, `name`, `level`) VALUES (6, LEFT(UUID(), 8), 1);
INSERT INTO `tours` (`id`, `name`, `level`) VALUES (7, LEFT(UUID(), 8), 1);
INSERT INTO `tours` (`id`, `name`, `level`) VALUES (8, LEFT(UUID(), 8), 1);
INSERT INTO `tours` (`id`, `name`, `level`) VALUES (9, LEFT(UUID(), 8), 2);
INSERT INTO `tours` (`id`, `name`, `level`) VALUES (10, LEFT(UUID(), 8), 2);
INSERT INTO `tours` (`id`, `name`, `level`) VALUES (11, LEFT(UUID(), 8), 2);
INSERT INTO `tours` (`id`, `name`, `level`) VALUES (12, LEFT(UUID(), 8), 2);

INSERT INTO `stops` (`id`, `name`) VALUES (1, LEFT(UUID(), 8));
INSERT INTO `stops` (`id`, `name`) VALUES (2, LEFT(UUID(), 8));
INSERT INTO `stops` (`id`, `name`) VALUES (3, LEFT(UUID(), 8));
INSERT INTO `stops` (`id`, `name`) VALUES (4, LEFT(UUID(), 8));
INSERT INTO `stops` (`id`, `name`) VALUES (5, LEFT(UUID(), 8));
INSERT INTO `stops` (`id`, `name`) VALUES (6, LEFT(UUID(), 8));
INSERT INTO `stops` (`id`, `name`) VALUES (7, LEFT(UUID(), 8));
INSERT INTO `stops` (`id`, `name`) VALUES (8, LEFT(UUID(), 8));
INSERT INTO `stops` (`id`, `name`) VALUES (9, LEFT(UUID(), 8));
INSERT INTO `stops` (`id`, `name`) VALUES (10, LEFT(UUID(), 8));
INSERT INTO `stops` (`id`, `name`) VALUES (11, LEFT(UUID(), 8));
INSERT INTO `stops` (`id`, `name`) VALUES (12, LEFT(UUID(), 8));

INSERT INTO `tours_stops` (`tours_id`, `stops_id`, `order`) VALUES (1, 1, 1);
INSERT INTO `tours_stops` (`tours_id`, `stops_id`, `order`) VALUES (1, 2, 2);
INSERT INTO `tours_stops` (`tours_id`, `stops_id`, `order`) VALUES (1, 3, 3);

INSERT INTO `tours_stops` (`tours_id`, `stops_id`, `order`) VALUES (2, 2, 1);
INSERT INTO `tours_stops` (`tours_id`, `stops_id`, `order`) VALUES (2, 3, 2);
INSERT INTO `tours_stops` (`tours_id`, `stops_id`, `order`) VALUES (2, 4, 3);

INSERT INTO `tours_stops` (`tours_id`, `stops_id`, `order`) VALUES (3, 3, 1);
INSERT INTO `tours_stops` (`tours_id`, `stops_id`, `order`) VALUES (3, 4, 2);
INSERT INTO `tours_stops` (`tours_id`, `stops_id`, `order`) VALUES (3, 5, 3);

INSERT INTO `tours_stops` (`tours_id`, `stops_id`, `order`) VALUES (4, 3, 1);
INSERT INTO `tours_stops` (`tours_id`, `stops_id`, `order`) VALUES (4, 4, 2);
INSERT INTO `tours_stops` (`tours_id`, `stops_id`, `order`) VALUES (4, 5, 3);

INSERT INTO `tours_stops` (`tours_id`, `stops_id`, `order`) VALUES (5, 4, 1);
INSERT INTO `tours_stops` (`tours_id`, `stops_id`, `order`) VALUES (5, 5, 2);
INSERT INTO `tours_stops` (`tours_id`, `stops_id`, `order`) VALUES (5, 6, 3);

INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (1, LEFT(UUID(), 8), 0);
INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (2, LEFT(UUID(), 8), 0);
INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (3, LEFT(UUID(), 8), 0);
INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (4, LEFT(UUID(), 8), 0);
INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (5, LEFT(UUID(), 8), 0);
INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (6, LEFT(UUID(), 8), 0);
INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (7, LEFT(UUID(), 8), 0);
INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (8, LEFT(UUID(), 8), 0);
INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (9, LEFT(UUID(), 8), 0);
INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (10, LEFT(UUID(), 8), 0);
INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (11, LEFT(UUID(), 8), 1);
INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (12, LEFT(UUID(), 8), 1);
INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (13, LEFT(UUID(), 8), 1);
INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (14, LEFT(UUID(), 8), 1);
INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (15, LEFT(UUID(), 8), 1);
INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (16, LEFT(UUID(), 8), 1);
INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (17, LEFT(UUID(), 8), 1);
INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (18, LEFT(UUID(), 8), 1);
INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (19, LEFT(UUID(), 8), 1);
INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (20, LEFT(UUID(), 8), 1);
INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (21, LEFT(UUID(), 8), 2);
INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (22, LEFT(UUID(), 8), 2);
INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (23, LEFT(UUID(), 8), 2);
INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (24, LEFT(UUID(), 8), 2);
INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (25, LEFT(UUID(), 8), 2);
INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (26, LEFT(UUID(), 8), 2);
INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (27, LEFT(UUID(), 8), 2);
INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (28, LEFT(UUID(), 8), 2);
INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (29, LEFT(UUID(), 8), 2);
INSERT INTO `tourists` (`id`, `name`, `level`) VALUES (30, LEFT(UUID(), 8), 2);

INSERT INTO `trips` (`id`, `duration`, `started`, `completed`, `leader_id`, `tours_id`) 
    VALUES (1, 2, 0, 0, 11, 1);
INSERT INTO `trips` (`id`, `duration`, `started`, `completed`, `leader_id`, `tours_id`) 
    VALUES (2, 3, 0, 0, 12, 2);
INSERT INTO `trips` (`id`, `duration`, `started`, `completed`, `leader_id`, `tours_id`) 
    VALUES (3, 4, 0, 0, 13, 3);
INSERT INTO `trips` (`id`, `duration`, `started`, `completed`, `leader_id`, `tours_id`) 
    VALUES (4, 5, 0, 0, 14, 4);
INSERT INTO `trips` (`id`, `duration`, `started`, `completed`, `leader_id`, `tours_id`) 
    VALUES (5, 6, 0, 0, 15, 5);
INSERT INTO `trips` (`id`, `duration`, `started`, `completed`, `leader_id`, `tours_id`) 
    VALUES (6, 7, 0, 0, 16, 6);
INSERT INTO `trips` (`id`, `duration`, `started`, `completed`, `leader_id`, `tours_id`) 
    VALUES (7, 2, 0, 0, 17, 7);
INSERT INTO `trips` (`id`, `duration`, `started`, `completed`, `leader_id`, `tours_id`) 
    VALUES (8, 3, 0, 0, 21, 11);

INSERT INTO `trips_tourists` (`trips_id`, `tourists_id`) VALUES (1, 1);
INSERT INTO `trips_tourists` (`trips_id`, `tourists_id`) VALUES (1, 2);
INSERT INTO `trips_tourists` (`trips_id`, `tourists_id`) VALUES (1, 3);
INSERT INTO `trips_tourists` (`trips_id`, `tourists_id`) VALUES (1, 4);
INSERT INTO `trips_tourists` (`trips_id`, `tourists_id`) VALUES (1, 5);
INSERT INTO `trips_tourists` (`trips_id`, `tourists_id`) VALUES (1, 6);

INSERT INTO `trips_tourists` (`trips_id`, `tourists_id`) VALUES (2, 1);
INSERT INTO `trips_tourists` (`trips_id`, `tourists_id`) VALUES (2, 2);
INSERT INTO `trips_tourists` (`trips_id`, `tourists_id`) VALUES (2, 3);
INSERT INTO `trips_tourists` (`trips_id`, `tourists_id`) VALUES (2, 4);
INSERT INTO `trips_tourists` (`trips_id`, `tourists_id`) VALUES (2, 5);
INSERT INTO `trips_tourists` (`trips_id`, `tourists_id`) VALUES (2, 6);

INSERT INTO `trips_tourists` (`trips_id`, `tourists_id`) VALUES (3, 1);
INSERT INTO `trips_tourists` (`trips_id`, `tourists_id`) VALUES (3, 2);
INSERT INTO `trips_tourists` (`trips_id`, `tourists_id`) VALUES (3, 3);
INSERT INTO `trips_tourists` (`trips_id`, `tourists_id`) VALUES (3, 4);
INSERT INTO `trips_tourists` (`trips_id`, `tourists_id`) VALUES (3, 5);
INSERT INTO `trips_tourists` (`trips_id`, `tourists_id`) VALUES (3, 6);

INSERT INTO `trips_stops` (`trips_id`, `stops_id`, `date`, `status`, `help`) 
    VALUES (1, 1, '2017-10-17 00:00:00', 'Ok', 'no help');

INSERT INTO `trips_stops` (`trips_id`, `stops_id`, `date`, `status`, `help`) 
    VALUES (1, 2, '2017-10-17 00:00:00', 'Ok', 'no help');

INSERT INTO `trips_stops` (`trips_id`, `stops_id`, `date`, `status`, `help`) 
    VALUES (1, 3, '2017-10-17 00:00:00', 'Ok', 'no help');

INSERT INTO `trips_stops` (`trips_id`, `stops_id`, `date`, `status`, `help`) 
    VALUES (2, 2, '2017-10-17 00:00:00', 'Ok', 'no help');

INSERT INTO `trips_stops` (`trips_id`, `stops_id`, `date`, `status`, `help`) 
    VALUES (2, 3, '2017-10-17 00:00:00', 'Ok', 'no help');

INSERT INTO `trips_stops` (`trips_id`, `stops_id`, `date`, `status`, `help`) 
    VALUES (2, 4, '2017-10-17 00:00:00', 'Ok', 'no help');

INSERT INTO `trips_stops` (`trips_id`, `stops_id`, `date`, `status`, `help`) 
    VALUES (3, 3, '2017-10-17 00:00:00', 'Ok', 'no help');

INSERT INTO `trips_stops` (`trips_id`, `stops_id`, `date`, `status`, `help`) 
    VALUES (3, 4, '2017-10-17 00:00:00', 'Ok', 'no help');

INSERT INTO `trips_stops` (`trips_id`, `stops_id`, `date`, `status`, `help`) 
    VALUES (3, 5, '2017-10-17 00:00:00', 'Ok', 'no help');
