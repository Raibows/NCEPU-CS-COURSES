package com.example.backstage.Service.InterviewService;

import com.example.backstage.Dao.InterviewDao.RefundDao;
import com.example.backstage.Entity.InterviewEntity.Refund;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;

import javax.transaction.Transactional;
import java.util.List;

@Service
@Transactional
public class RefundService {
    @Autowired
    private RefundDao dao;

    /**
     *
     * @param refund
     */
    public void addRefund(Refund refund){
        dao.save(refund);
    }

    /**
     *
     * @param pageable
     * @return
     */
    public Page<Refund> findAllByPage(String name, Pageable pageable){
        return dao.findAllByPage(name,pageable);
    }
}
