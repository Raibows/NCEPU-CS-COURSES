package com.example.backstage.Dao.WebSearchDao;

import com.example.backstage.Entity.WebSearchEntity.Announcement;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

import java.util.Date;
import java.util.List;

@Repository
public interface AnnouncementDao extends JpaRepository<Announcement,String> {

    /**
     *
     * @param pageable
     * @return
     */
    @Query(value = "select * from announcement",nativeQuery = true)
    Page<Announcement> findAllByPage(Pageable pageable);

    /**
     *
     * @param id
     */
    void deleteById(int id);

    /**
     *
     * @param date
     * @return
     */
    Announcement findByPublishDate(Date date);


}
