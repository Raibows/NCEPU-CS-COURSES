package com.example.backstage.Service.InterviewService;

import com.example.backstage.Dao.InterviewDao.CheckDao;
import com.example.backstage.Entity.InterviewEntity.Check;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;

import javax.transaction.Transactional;

@Service
@Transactional
public class CheckService {
    @Autowired
    private CheckDao dao;

    /**
     *
     * @param check
     */
    public void addCheck(Check check){
        dao.save(check);
    }

    /**
     *
     * @param name
     * @param pageable
     * @return
     */
    public Page<Check> findAll(String name, Pageable pageable){
        return dao.findAllByAll(name,pageable);
    }

}
