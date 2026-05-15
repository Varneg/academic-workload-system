SELECT 
        CONCAT(t.SName, ' ', t.FName, ' ', IFNULL(t.LName, '')) AS PIB,
        t.PostID,
        ly.Rate,
        ly.TimeOtherLoad
        
FROM
	teacher t
 
JOIN
	loadaonyear ly 
		ON t.TecherID = ly.TeacherID AND ly.AcademicYear = :yearConfig
        
WHERE
	t.TecherID = :teacherID