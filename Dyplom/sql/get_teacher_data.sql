SELECT 
    t.TecherID,
    CONCAT(t.SName, ' ', t.FName, ' ', IFNULL(t.LName, '')) AS PIB,

    SUM(CASE 
        WHEN MOD(x.Semester, 2) = 1 THEN x.GeneralTime
        ELSE 0 
    END) AS Semester1,

    SUM(CASE 
        WHEN MOD(x.Semester, 2) = 0 THEN x.GeneralTime
        ELSE 0 
    END) AS Semester2,

    loy.TimeOtherLoad,

    SUM(x.GeneralTime) + loy.TimeOtherLoad AS TotalLoad,

    loy.Rate,
    p.PostName,

    SUM(x.TimePerWeek) AS WeeklyLoad

FROM Teacher t

LEFT JOIN (
    SELECT DISTINCT
        tl.TecherID,
        da.DisciplineActivity,
        da.GeneralTime,
        da.TimePerWeek,
        da.Semester
    FROM TeachingLoad tl
    JOIN DisciplineActivity da
        ON da.DisciplineActivity = tl.DisciplineActivityID
    WHERE da.DisciplineYear = :yearConfig
) x ON x.TecherID = t.TecherID

INNER JOIN LoadaOnYear loy 
    ON loy.TeacherID = t.TecherID 
    AND loy.AcademicYear = :yearConfig

INNER JOIN Post p 
    ON p.PostID = t.PostID

GROUP BY 
    t.TecherID,
    loy.TimeOtherLoad,
    loy.Rate,
    p.PostName;