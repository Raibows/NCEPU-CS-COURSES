<template>
  <div>
    <h1 style="margin-left: 600px;color: gray">借书表</h1>
    <el-table
      :data="data"
      border
      style="width: 60%;"
    >
      <el-table-column
        prop="stuid"
        label="学号"
        width="120"
      />
      <el-table-column
        prop="bookName"
        label="书名"
        width="120"
      />
      <el-table-column
        prop="borrowDate"
        label="借阅时间"
        width="120"
      />
      <el-table-column
        prop="returnDate"
        label="还书时间"
        width="120"
      />
      <el-table-column
        prop="isbn"
        label="ISBN"
        width="150"
      />
      <el-table-column
        prop="status"
        label="状态"
        width="160"
      >
        <template slot-scope="scope">
          <el-tag
            :type="scope.row.status === 1 ? 'success' : 'danger'"
            disable-transitions
          >{{ scope.row.status === 1 ? '已还' : '未还' }}
          </el-tag>
        </template>
      </el-table-column>
    </el-table>
    <el-row style="margin-top: 20px;">
      <el-col :span="6" :offset="8">
        <el-pagination
          :current-page="currentPage"
          :page-sizes="[5, 10, 30, 50]"
          :page-size="pageSize"
          layout="total, sizes, prev, pager, next, jumper"
          :total="total"
          @size-change="handleSizeChange"
          @current-change="handleCurrentChange"
        />
      </el-col>
    </el-row>
    <user-form ref="userForm" />
  </div>

</template>

<script>
import { searchBorrow } from '@/api/borrow'
export default {
  name: 'CirculationSearch',
  data() {
    return {
      data: [],
      pageSize: 5,
      currentPage: 1,
      total: 0
    }
  },

  created() {
    this.search()
  },
  methods: {
    search() {
      searchBorrow({
        stuid: this.$store.getters.userId, pageNum: this.currentPage, pageSize: this.pageSize
      }).then(response => {
        this.data = response.data.list
        this.currentPage = response.data.pageNum,
        this.total = response.data.total,
        this.pageSize = response.data.size
        console.log(response.data.isbn)
      })
    },
    handleSizeChange(val) {
      this.pageSize = val
      this.search()
    },
    handleCurrentChange(val) {
      this.currentPage = val
      this.search()
    }
  }

}
</script>

<style lang="scss" scoped>
.el-table{
  left: 20%;
}
</style>
