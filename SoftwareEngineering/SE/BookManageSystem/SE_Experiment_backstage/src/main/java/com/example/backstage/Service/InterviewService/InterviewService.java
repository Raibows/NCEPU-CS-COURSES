package com.example.backstage.Service.InterviewService;

import com.example.backstage.Dao.InterviewDao.InterviewDao;
import com.example.backstage.Entity.InterviewEntity.Interview;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;

import javax.transaction.Transactional;

@Service
@Transactional
public class InterviewService {
    @Autowired
    private InterviewDao dao;

    /**
     *
     * @param interview
     */
    public void addInterview(Interview interview){
        dao.save(interview);
    }

    /**
     *
     * @param id
     * @return
     */
    public Interview findInterviewById(String id){
        return dao.findInterviewById(id);
    }

    public Page<Interview> findAll(String name,Pageable pageable){
        return dao.findAllByAll(name,pageable);
    }

    /**
     *
     * @param id
     */
    public void deleteById(String id){
        dao.deleteById(id);
    }

    /**
     *
     * @param isbn
     */
    public void deleteByIsbn(String isbn){
        dao.deleteByIsbn(isbn);
    }

}
