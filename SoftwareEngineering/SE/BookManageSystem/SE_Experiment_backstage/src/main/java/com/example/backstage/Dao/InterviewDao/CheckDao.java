package com.example.backstage.Dao.InterviewDao;

import com.example.backstage.Entity.InterviewEntity.Check;
import com.example.backstage.Entity.InterviewEntity.Interview;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

@Repository
public interface CheckDao extends JpaRepository<Check,String> {
    /**
     *
     * @param pageable
     * @return
     */
    /**
     *
     * @param pageable
     * @return
     */
    @Query(value = "SELECT checklist.id,bookSeller,userId,bookName,isbn,num,user.name FROM checklist JOIN user where user.id=checklist.userId and (bookName like "
            +"%"+":name"+"%"+" or checklist.id like "+"%"+":name"+"%"+
            " or userId like "+"%"+":name"+"%"+" or isbn like "+"%"+":name"+"%"+" or num like "+"%"+":name"+"%)",
            countQuery = "SELECT count(*) FROM checklist JOIN user where user.id=checklist.userId and (bookName like "
                    +"%"+":name"+"%"+" or checklist.id like "+"%"+":name"+"%"+
                    " or userId like "+"%"+":name"+"%"+" or isbn like "+"%"+":name"+"%"+" or num like "+"%"+":name"+"%)"
            ,nativeQuery = true)
    Page<Check> findAllByAll(@Param("name")String name, Pageable pageable);


}
