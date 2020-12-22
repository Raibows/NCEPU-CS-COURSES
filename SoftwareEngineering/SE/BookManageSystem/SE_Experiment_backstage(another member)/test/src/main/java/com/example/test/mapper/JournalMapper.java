package com.example.test.mapper;

import com.example.test.bean.JournalBean;
import com.example.test.bean.JournalSubscribeInfo;
import org.apache.ibatis.annotations.Delete;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;
import org.springframework.stereotype.Repository;
import org.springframework.stereotype.Service;

import java.util.List;

@Repository
public interface JournalMapper {

    /*********************************   期刊查询  ********************************************************/
    @Select("select * from journal where period like concat (concat ('%',#{period}),'%')")
    List<JournalBean> SearchJournal(String period);

    /*********************************   期刊添入  ********************************************************/
    @Insert("insert into journal values (#{no},#{journalName},#{startYear},#{period},#{description})")
    boolean AddJournal(String no,String journalName,String startYear,String period,String description);

    /*********************************   期刊删除  ********************************************************/
    @Delete("delete from journal where no = #{no}")
    boolean DeleteJournal(String no);

    /********************************   期刊信息修改  ********************************************************/


    //修改刊期、描述
    @Update("update journal set description=#{description},period=#{period} where no=#{no}")
    boolean ModifyJournal(String no,String description,String period);

    /********************************     期刊订阅  ********************************************************/
    //期刊订阅
    @Insert("insert into journalsubscribe set journalNo = #{journalNo},stuId=#{stuId},journalName=#{journalName},period=#{period},description=#{description} ")
    boolean JournalSubscibe(String journalNo,String stuId,String journalName,String period,String description);

    /********************************     期刊取消订阅  ********************************************************/
    //期刊取消订阅
    @Delete("delete from journalsubscribe where journalNo=#{journalNo} and stuId=#{stuId} ")
    boolean JournalCancel(String journalNo,String stuId);

    /********************************     查看订阅  ********************************************************/
    @Select("select * from journalsubscribe  where stuId=#{stuId} ")
    List<JournalSubscribeInfo> SearchSubscribe(String stuId );




}
