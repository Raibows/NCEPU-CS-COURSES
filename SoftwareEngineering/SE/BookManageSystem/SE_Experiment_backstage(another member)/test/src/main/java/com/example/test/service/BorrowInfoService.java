package com.example.test.service;

import com.example.test.bean.BorrowInfo;

import java.util.Date;
import java.util.List;

public interface BorrowInfoService {
    List<BorrowInfo> getBorrowInfo_By_ID(String ID );
    List<BorrowInfo> getUnreturnInfo_By_ID(String ID);
    int ReviewBookCondition(String ISBN );
    int ReviewBorrConditon(String StuID );
    boolean BorrowBook( String StuID, String ISBN , Date date );
    boolean SetBorrowedBook(String ISBN );
    boolean SetBorrowedStudent(String StuID);
    boolean ReturnBook(String StuID, String ISBN, Date date);
    boolean SetReturnedStudent(String StuID);
    boolean SetReturnedBook(String ISBN );
    int overdue( String stuid, String ISBN );
    int getOverdueDays(String id,String ISBN );
    int ReviewReturnStatus(String StuID,String ISBN );
    boolean ReturnStatus(String StuID,String ISBN);
    int SetPenalty(int days,String stuid);
}
