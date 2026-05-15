SELECT 
    da.DisciplineActivity AS ID,
    d.DisciplineName AS Discipline,
    ta.ActivityName AS ActivityType,

    CASE
        WHEN ta.IsGroupLoad = FALSE THEN CONCAT(       
            sp.SpecialityName, '-',
            RIGHT(sg.GroupYear, 2)
        )
        ELSE CONCAT(
            sp.SpecialityName, '-',
            RIGHT(sg.GroupYear, 2), '-',
            sg.GroupNumber
        )
    END AS `Group`,

    da.TimePerWeek,
    da.GeneralTime,
    da.Semester,

    CASE
        WHEN da.QuantityStudent IS NOT NULL THEN da.QuantityStudent

        WHEN ta.IsGroupLoad = FALSE THEN (
            SELECT SUM(qs.QuantityStudent)
            FROM StudentGroup sg2
            JOIN QuantityStudentOnGroup qs 
                ON qs.StudentGroupID = sg2.StudentGroupID
            WHERE sg2.SpecialityNumber = sg.SpecialityNumber
              AND qs.SettingsYear = da.DisciplineYear
              AND sg2.GroupYear = sg.GroupYear
        )

        ELSE qs_main.QuantityStudent
    END AS StudentsQuantity,

    CASE 
        WHEN t.TecherID IS NULL THEN NULL
        ELSE CONCAT(t.SName, ' ', t.FName, ' ', IFNULL(t.LName, ''))
    END AS TeacherName

FROM DisciplineActivity da

JOIN Discipline d 
    ON d.DisciplineID = da.DisciplineID

JOIN TypeActivity ta 
    ON ta.ActivityID = da.ActivityID

LEFT JOIN StudentGroup sg 
    ON sg.StudentGroupID = da.StudentGroupID

LEFT JOIN Speciality sp
    ON sp.SpecialityNumber = sg.SpecialityNumber

LEFT JOIN QuantityStudentOnGroup qs_main 
    ON qs_main.StudentGroupID = sg.StudentGroupID
    AND qs_main.SettingsYear = da.DisciplineYear

LEFT JOIN TeachingLoad tl 
    ON tl.DisciplineActivityID = da.DisciplineActivity

LEFT JOIN Teacher t 
    ON t.TecherID = tl.TecherID

WHERE da.DisciplineYear = :yearConfig;