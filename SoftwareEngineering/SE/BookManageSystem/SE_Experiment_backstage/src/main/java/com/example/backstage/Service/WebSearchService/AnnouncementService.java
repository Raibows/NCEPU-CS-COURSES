package com.example.backstage.Service.WebSearchService;

import com.example.backstage.Dao.WebSearchDao.AnnouncementDao;
import com.example.backstage.Entity.WebSearchEntity.Announcement;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;

import javax.transaction.Transactional;
import java.util.Date;
import java.util.List;

@Service
@Transactional
public class AnnouncementService {
    @Autowired
    private AnnouncementDao announcementDao;

    /**
     *
     * @param pageable
     * @return
     */
    public Page<Announcement> findAllByPage(Pageable pageable){
        return announcementDao.findAllByPage(pageable);
    }

    /**
     *
     * @param id
     */
    public void deleteAnnouncement(int id){
        announcementDao.deleteById(id);
    }

    /**
     *
     * @param date
     * @return
     */
    public Announcement findByDate(Date date){
        return announcementDao.findByPublishDate(date);
    }

    /**
     *
     * @param announcement
     */
    public void addAnnouncement(Announcement announcement){
        announcementDao.save(announcement);
    }

}
