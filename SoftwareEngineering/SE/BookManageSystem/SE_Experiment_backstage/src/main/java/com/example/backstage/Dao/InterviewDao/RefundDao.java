package com.example.backstage.Dao.InterviewDao;

import com.example.backstage.Entity.InterviewEntity.Refund;
import com.example.backstage.Entity.MaintainEntity.Book;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface RefundDao extends JpaRepository<Refund,String> {

    /**
     *
     * @param pageable
     * @return
     */
    @Query(value = "SELECT isbn,userId,orderDate,price,reason,num,state,user.name FROM refund JOIN user where user.id=refund.userId and (isbn like "
            +"%"+":name"+"%"+" or userId like "+"%"+":name"+"%"+
            " or orderDate like "+"%"+":name"+"%"+" or price like "+"%"+":name"+"%"+" or reason like "+"%"+":name"+"%"+" or num like "
            +"%"+":name"+"%"+" or state like "+"%"+":name"+"%)",
            countQuery = "SELECT count(*) FROM refund JOIN user where user.id=refund.userId and (isbn like "
                    +"%"+":name"+"%"+" or userId like "+"%"+":name"+"%"+
                    " or orderDate like "+"%"+":name"+"%"+" or price like "+"%"+":name"+"%"+" or reason like "+"%"+":name"+"%"+" or num like "
                    +"%"+":name"+"%"+" or state like "+"%"+":name"+"%)"
            ,nativeQuery = true)
    Page<Refund> findAllByPage(@Param("name")String name, Pageable pageable);
}
