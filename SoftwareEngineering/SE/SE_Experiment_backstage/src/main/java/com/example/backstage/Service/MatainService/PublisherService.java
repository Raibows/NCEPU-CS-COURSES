package com.example.backstage.Service.MatainService;

import com.example.backstage.Dao.MaintainDao.PublisherDao;
import com.example.backstage.Entity.MaintainEntity.Publisher;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;

import javax.transaction.Transactional;
import java.util.List;

@Service
@Transactional
public class PublisherService {
    @Autowired
    PublisherDao publisherDao;

    /**
     * @param name
     * @return
     */
    public List<Publisher> findPublisherByName(String name) {
        return publisherDao.findByPublisherNameLike("%"+name+"%");
    }

    /**
     * @param publisher
     */
    public void addPublisher(Publisher publisher) {
        publisherDao.save(publisher);
    }

    /**
     *
     * @param number
     * @return
     */
    public Publisher findPublisherByPhone(String number){
        return publisherDao.findByPhoneNumber(number);
    }


    /**
     *
     * @param
     * @return
     */
    public Page<Publisher> findAllByPage(String name, Pageable pageable){
        return publisherDao.findAllByPage(name,pageable);
    }

    /**
     *
     * @param name
     * @return
     */
    public List<Publisher> findAllIdName(String name){
        return publisherDao.findAllIdName(name);
    }

    public void deleteById(int id){
        publisherDao.deleteById(id);
    }
}
