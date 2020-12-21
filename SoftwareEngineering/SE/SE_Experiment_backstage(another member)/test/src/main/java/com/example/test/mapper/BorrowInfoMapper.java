package com.example.test.mapper;

import com.example.test.bean.BorrowInfo;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;
import org.springframework.stereotype.Component;
import org.springframework.stereotype.Repository;

import java.util.Calendar;
import java.util.Date;
import java.util.List;

@Repository
public interface BorrowInfoMapper {

    /*********************************   查询借书 ********************************************************/
    //根据学号查询全部借书信息 id
    @Select("select bookinfo.bookName , borrow_info.* from borrow_info join bookinfo on borrow_info.isbn=bookinfo.isbn  where borrow_info.stuid = #{ID} ")
    List<BorrowInfo> getBorrowInfo_By_ID(String ID);

    //根据学号查询全部借书信息 id
    @Select("select bookinfo.bookName , borrow_info.* from borrow_info join bookinfo on borrow_info.isbn=bookinfo.isbn  where borrow_info.stuid = #{ID} and borrow_info.status = 0 ")
    List<BorrowInfo> getUnreturnInfo_By_ID(String ID);


    /*********************************     借书        ********************************************************/
    //根据ISBN查询库存是否有对应图书、返回该本书 1--可被借 0--不可  （ num = 0 --不可借 num > 0 -- 可借  ）
    @Select("select count(*) from bookinfo where isbn=#{ISBN} and num>0  ;")
    int ReviewBookCondition(String ISBN );

    //审核读者的借书条件 (方法重在实现，判断查询出的数目是否为 1 ，若为 1 则该读者可借书 ，为 0 不可借书 )
    @Select("select count(*) from SE_Experiment.user where id=#{StuID} and borrowNum >= 1  ;")
    int ReviewBorrConditon(String StuID );

    //根据学号和ISBN 当前日期 生成 一条借书信息
    @Insert("Insert into SE_Experiment.borrow_info set stuid=#{StuID},isbn=#{ISBN},borrowDate=#{date} ;  ")
    boolean BorrowBook( String StuID, String ISBN , Date date );

    //根据ISBN号将对应的图书 可借数目 - 1 （不可借）
    @Update("update SE_Experiment.bookinfo set num=num-1 where isbn=#{ISBN} ")
    boolean SetBorrowedBook(String ISBN );

    //根据学号将 对应读者的 可借书数量 减一
    @Update("update SE_Experiment.user set  borrowNum=borrowNum-1 where id=#{StuID} ; ")
    boolean SetBorrowedStudent(String StuID);

    /*********************************     还书        ********************************************************/
    //根据 学号 和 ISBN 判断  1-- 当前借书信息 status 为 0  2-- ReturnDate 为 null
    @Select("select count(*) from borrow_info where stuid=#{StuID} and isbn=#{ISBN} and status=0 ")
    int ReviewReturnStatus(String StuID,String ISBN);

    //根据 学号 和 ISBN 当前日期 来还书(即在对应借阅信息加上还书日期？)
    @Update("Update SE_Experiment.borrow_info SET returnDate = #{date} where stuid=#{StuID} and isbn=#{ISBN} ")
    boolean ReturnBook(String StuID, String ISBN, Date date);

    //根据 学号 和 ISBN 还书 把status 改为1
    @Update("update SE_Experiment.borrow_info set status=1 where stuid=#{StuID} and isbn=#{ISBN};")
    boolean ReturnStatus(String StuID,String ISBN);

    //根据学号将 对应读者的 可借书数量 加一
    @Update("update SE_Experiment.user set  borrowNum=borrowNum+1 where id=#{StuID} ; ")
    boolean SetReturnedStudent(String StuID);

    //根据ISBN号将对应的图书 可借数目 + 1 （可借）
    @Update("update SE_Experiment.bookinfo set num=num+1 where isbn=#{ISBN} ")
    boolean SetReturnedBook(String ISBN );



    /*********************************     罚款        ********************************************************/
    //根据 借书日期 和 还书日期 和 可借期限 判断是否超期 ( 0--未超期 1--已超期  )
    @Select(" select count(*) from borrow_info where stuid=#{stuid} and isbn=#{ISBN} and datediff(returnDate,borrowDate) >= BorrowPeriod ;")
    int overdue( String stuid, String ISBN );

    // 若 逾期 得到 逾期天数  (再在实现时 用 days × 每日罚款即可 )
    @Select("select datediff(returnDate,borrowDate) as days from SE_Experiment.borrow_info where stuid=#{id} and isbn=#{ISBN} limit 1  ")
    int getOverdueDays(String id,String ISBN );

    //修改 用户表 罚款金额 （在controller中获取 days 再 × 每日罚款 修改 用户表 penalty ）
    @Update("update user set penalty=penalty+#{days}*0.5 where id=#{stuid} ")
    int SetPenalty(int days,String stuid);

}
